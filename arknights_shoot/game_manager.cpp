#include"graphics.h"
#include"game_manager.h"
#include <conio.h>
#include "character.h"
#include"weapon.h"
#include <windows.h>



void game_manager::process_input() {
    if (m_state == MENU) {
        // ʹ�� kbhit �� getch ���س���
        if (_kbhit()) {
            int key = _getch();
            if (key == VK_RETURN) {
                m_state = RUNNING;
            }
        }
    }
    if (m_state == RUNNING) {
        float current_time = GetTickCount() / 1000.0f;  // ��ǰʱ�䣨�룩
        // ����������������
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            m_player.shoot(current_time);  // ���ݵ�ǰʱ�����ڹ�������ж�
        }
        // ����ƶ�����
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            m_player.set_velocity_x(-5);
            m_player.set_facing_right(false); // �����ƶ������ó���Ϊ��
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            m_player.set_velocity_x(5);
            m_player.set_facing_right(true); // �����ƶ������ó���Ϊ��
        }
        else {
            m_player.set_velocity_x(0);
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) m_player.jump();
    }
}

void game_manager::update() {
    if (m_state != RUNNING) return;

    static float last_time = 0.0f;
    float current_time = GetTickCount() / 1000.0f;
    float delta_time = current_time - last_time;
    last_time = current_time;
    // �����������
    m_physics.apply_gravity(m_player);
    
    // Ԥ���ɫ��һ��λ��
    Vector2 nextPos = m_player.get_pos();
    nextPos.x += m_player.get_velocity().x;
    nextPos.y += m_player.get_velocity().y;
    // ����һ����ʱ��ɫ������ײ���
    player tempPlayer = m_player;
    tempPlayer.get_pos() = nextPos;

    if (m_physics.check_platform_collision(tempPlayer, m_game_map)) {
        // ���������ײ��ʹ����ʱ��ɫ��λ�ø������λ��
        m_player.get_pos() = tempPlayer.get_pos();
        m_player.set_velocity_y(0);
        m_player.set_is_grounded(true);
    }
    else {
        // ���û����ײ���������λ��
        m_player.get_pos() = nextPos;
        m_player.set_is_grounded(false);
    }
     /*���µ���*/
    for (auto& enemy : m_enemies) {
        m_physics.apply_gravity(enemy);

        enemy.get_pos().y += enemy.get_velocity().y;

        m_physics.check_platform_collision(enemy, m_game_map);

        enemy.update();  
        // ��AI�������ƶ�
        //enemy.get_velocity().x = 2;  // ʾ���ƶ��߼�
    }
    // �����ӵ�-������ײ
    for (auto& enemy : m_enemies) {
        m_physics.apply_gravity(enemy);

        // ���µ���λ�ã�ͬʱ����x��y�ᣩ
        Vector2 enemy_vel = enemy.get_velocity();
        enemy.get_pos().x += enemy_vel.x;  // ���x��λ�ø���
        enemy.get_pos().y += enemy_vel.y;  // ԭ��y��λ�ø���

        m_physics.check_platform_collision(enemy, m_game_map);
        enemy.update();  

        // �ӵ�-������ײ���
        for (auto& bullet : m_player.getWeapon().get_bullets()) {
            if (bullet.get_alive() && m_physics.check_bullet_enemy_collision(bullet, enemy)) {
                // ������˷����ӵ����з���
                float bullet_dir = bullet.get_velocity().x > 0 ? 1.0f : -1.0f;

                // �������ˣ������������Ϊ10���ɸ������������
                enemy.apply_knockback(10.0f, bullet_dir);

                // ����ӵ�ʧЧ
                bullet.set_alive(false);
            }
        }
    }
    // �����ӵ�
     m_player.getWeapon().update(delta_time);

    // �������Ƿ����
    for (auto& enemy : m_enemies) {
        if (m_physics.check_map_bounds(enemy, m_game_map)) {
            enemy.set_alive(false);  // ��ǵ�����̭
        }
    }
     // ����ͼ�߽�
    if (m_physics.check_map_bounds(m_player, m_game_map)) {

    }
    // ���½�ɫ����
    m_player.update();
}

void game_manager::draw() {
    
    

    if (m_state == LOADING) {
        // ��ʾ�����е���ʾ
        settextcolor(WHITE);
        outtextxy(500, 360, "loading");
        settextstyle(30, 0, _T("΢���ź�"));
        outtextxy(500, 360, "������...");
    }
    
    else if (m_state == RUNNING) {
        // ������Ϸ����
        m_game_map.draw();
        m_player.draw();
        m_player.getWeapon().draw();  // �����ӵ�
        for (auto& enemy : m_enemies) enemy.draw();  // ���Ƶ���
    }
}


void game_manager::run() {
    initgraph(1280, 720);

    // �����Ҫ���ص���Դ�б�
    std::vector<std::pair<std::string, const char*>> resources = {
        {"player_idle_right", "./res/chars/walk_right_1.png"},  // �������ͼƬ
        {"player_idle_left", "./res/chars/walk_left_1.png"},    // �������ͼƬ
        {"enemy_idle_right", "./res/chars/move_02_right.png"}, // ��������ͼƬ
        {"enemy_idle_left", "./res/chars/move_02_left.png"},   // ��������ͼƬ
        {"platform", "./res/platforms/1.png"},
        {"bullet", "./res/bullets/2.png"}
    };
    size_t current_load_index = 0;  // ��ǰ���ص���Դ����

    while (true) {
        BeginBatchDraw();
        process_input();

            
        // ��֡������Դ��ÿ֡����1��������������
        if (current_load_index < resources.size()) {
            std::pair<std::string, const char*>& resourcePair = resources[current_load_index];
            std::string key = resourcePair.first;
            const char* path = resourcePair.second;
            bool load_success = resource_manage::get_instance().load_image(key, path);
            if (!load_success) {
                // �������ʧ�ܣ������������־��
                OutputDebugStringA("��Դ����ʧ��: ");
                OutputDebugStringA(path);
            }
            current_load_index++;
        }
        else {
            // ������Դ������ɺ��л�״̬
            m_state = RUNNING;
        }

        if (m_state == RUNNING) {
            update();
            draw();
        }
        else {
            // ��ʾ�����е���ʾ�������֣�
            settextcolor(WHITE);
            const char loadingText[13] = "������...";
            //outtextxy(500, 360, loadingText);

            
        }
        draw();

        EndBatchDraw();
        Sleep(16);
    }
}