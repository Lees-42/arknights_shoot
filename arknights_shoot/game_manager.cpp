#include"graphics.h"
#include"game_manager.h"
#include <conio.h>
#include "character.h"
#include"weapon.h"
#include <windows.h>

// game_manager.cpp
int game_manager::get_alive_enemy_count() const {
    int count = 0;
    for (const auto& enemy : m_enemies) {
        if (enemy.get_alive()) count++;
    }
    return count;
}

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
        if (GetAsyncKeyState('J') & 0x8000) {
            m_player.shoot(current_time);  // ���ݵ�ǰʱ�����ڹ�������ж�
        }
        // ����ƶ�����
        if (GetAsyncKeyState('A') & 0x8000) {
            m_player.set_velocity_x(-5);
            m_player.set_facing_right(false); // �����ƶ������ó���Ϊ��
        }
        else if (GetAsyncKeyState('D') & 0x8000) {
            m_player.set_velocity_x(5);
            m_player.set_facing_right(true); // �����ƶ������ó���Ϊ��
        }
        else {
            m_player.set_velocity_x(0);
        }
        if (GetAsyncKeyState('W') & 0x8000) m_player.jump();
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
    m_enemy_spawn_timer += delta_time; // �ۼ�ʱ��

    // ��ʱ�䳬������Ҵ�����<3ʱ����
    if (m_enemy_spawn_timer >= m_enemy_spawn_interval &&
        get_alive_enemy_count() < 3) {

        const auto& platforms = m_game_map.get_platforms();
        if (platforms.empty()) return; // ��ƽ̨������

        // ���ѡһ��ƽ̨
        std::uniform_int_distribution<int> dist(0, platforms.size() - 1);
        int platform_idx = dist(m_rng);
        const auto& platform = platforms[platform_idx];

        // �����������λ�ã�ƽ̨������x�����
        RECT plat_rect = platform.get_rect();
        float enemy_x = std::uniform_real_distribution<float>(
            plat_rect.left, plat_rect.right - 64  // 64�ǵ������ɿ�ȣ���enemy����һ�£�
        )(m_rng);
        float enemy_y = plat_rect.top - 90;       

        // �����µ��˲���ӵ��б�
        m_enemies.emplace_back(enemy_x, enemy_y);

        // ���ü�ʱ��
        m_enemy_spawn_timer = 0.0f;
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
        {"enemy_idle_right", "./res/chars/watcher1.png"}, // ��������ͼƬ
        {"enemy_idle_left", "./res/chars/watcher1.png"},   // ��������ͼƬ
        {"platform", "./res/platforms/1.png"},
        {"bullet", "./res/bullets/2.png"},
        {"game_map", "./res/bg.png"}
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