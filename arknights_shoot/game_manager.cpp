#include"graphics.h"
#include"game_manager.h"
#include <conio.h>
#include "character.h"
#include"weapon.h"
#include <windows.h>



void game_manager::process_input() {
    if (m_state == MENU) {
        // 使用 kbhit 和 getch 检测回车键
        if (_kbhit()) {
            int key = _getch();
            if (key == VK_RETURN) {
                m_state = RUNNING;
            }
        }
    }
    if (m_state == RUNNING) {
        float current_time = GetTickCount() / 1000.0f;  // 当前时间（秒）
        // 攻击键（左键）检测
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            m_player.shoot(current_time);  // 传递当前时间用于攻击间隔判断
        }
        // 玩家移动控制
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) m_player.set_velocity_x(-5);
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) m_player.set_velocity_x(5);
        else m_player.set_velocity_x(0);

        if (GetAsyncKeyState(VK_SPACE) & 0x8000) m_player.jump();
    }
}

void game_manager::update() {
    if (m_state != RUNNING) return;

    static float last_time = 0.0f;
    float current_time = GetTickCount() / 1000.0f;
    float delta_time = current_time - last_time;
    last_time = current_time;
    // 更新玩家物理
    m_physics.apply_gravity(m_player);
    
    // 预测角色下一个位置
    Vector2 nextPos = m_player.get_pos();
    nextPos.x += m_player.get_velocity().x;
    nextPos.y += m_player.get_velocity().y;
    // 创建一个临时角色用于碰撞检测
    player tempPlayer = m_player;
    tempPlayer.get_pos() = nextPos;

    if (m_physics.check_platform_collision(tempPlayer, m_game_map)) {
        // 如果发生碰撞，使用临时角色的位置更新玩家位置
        m_player.get_pos() = tempPlayer.get_pos();
        m_player.set_velocity_y(0);
        m_player.set_is_grounded(true);
    }
    else {
        // 如果没有碰撞，更新玩家位置
        m_player.get_pos() = nextPos;
        m_player.set_is_grounded(false);
    }
     /*更新敌人*/
    for (auto& enemy : m_enemies) {
        m_physics.apply_gravity(enemy);
        enemy.get_pos().y += enemy.get_velocity().y;
        m_physics.check_platform_collision(enemy, m_game_map);
        // 简单AI：左右移动
        //enemy.get_velocity().x = 2;  // 示例移动逻辑
    }
    for (auto& enemy : m_enemies) {
        m_physics.apply_gravity(enemy);
        m_physics.check_platform_collision(enemy, m_game_map);
        enemy.update();  // 敌人AI逻辑（如移动）

        // 子弹-敌人碰撞检测
        for (auto& bullet : m_player.getWeapon().get_bullets()) {  // 改为非 const 引用
            if (bullet.get_alive() && m_physics.check_bullet_enemy_collision(bullet, enemy)) {
                // 1. 计算击退方向（根据子弹速度方向）
                float bullet_dir = bullet.get_velocity().x > 0 ? 1.0f : -1.0f;
                // 2. 应用击退（力度由子弹的 knockback 决定）
                enemy.apply_knockback(bullet.get_knockback(), bullet_dir);
                // 3. 标记子弹为已击中（后续会被武器系统销毁）
                bullet.set_alive(false);
            }
        }
    }
    // 更新子弹
     m_player.getWeapon().update(delta_time);

    // 检测敌人是否掉落
    for (auto& enemy : m_enemies) {
        if (m_physics.check_map_bounds(enemy, m_game_map)) {
            enemy.set_alive(false);  // 标记敌人淘汰
        }
    }
     // 检查地图边界
    if (m_physics.check_map_bounds(m_player, m_game_map)) {

    }
}

void game_manager::draw() {
    
    

    if (m_state == LOADING) {
        // 显示加载中的提示（原逻辑）
        settextcolor(WHITE);
        outtextxy(500, 360, "loading");
        settextstyle(30, 0, _T("微软雅黑"));
        outtextxy(500, 360, "加载中...");
    }
    
    else if (m_state == RUNNING) {
        // 正常游戏绘制（原逻辑）
        m_game_map.draw();
        m_player.draw();
        m_player.getWeapon().draw();  // 绘制子弹
        for (auto& enemy : m_enemies) enemy.draw();  // 绘制敌人
    }
}


void game_manager::run() {
    initgraph(1280, 720);
    //setcaption("明日方舟射击游戏");

    // 标记需要加载的资源列表
    std::vector<std::pair<std::string, const char*>> resources = {
        {"player_idle", "./res/chars/move_02.png"},
        {"enemy_idle", "./res/chars/move_02.png"},
        {"platform", "./res/platforms/1.png"},
        {"bullet", "./res/bullets/1.png"}
    };
    size_t current_load_index = 0;  // 当前加载的资源索引

    while (true) {
        BeginBatchDraw();
        process_input();

            
        // 分帧加载资源（每帧加载1个，避免阻塞）
        if (current_load_index < resources.size()) {
            std::pair<std::string, const char*>& resourcePair = resources[current_load_index];
            std::string key = resourcePair.first;
            const char* path = resourcePair.second;
            bool load_success = resource_manage::get_instance().load_image(key, path);
            if (!load_success) {
                // 处理加载失败（如输出错误日志）
                OutputDebugStringA("资源加载失败: ");
                OutputDebugStringA(path);
            }
            current_load_index++;
        }
        else {
            // 所有资源加载完成后切换状态
            m_state = RUNNING;
        }

        if (m_state == RUNNING) {
            update();
            draw();
        }
        else {
            // 显示加载中的提示（如文字）
            settextcolor(WHITE);
            const char loadingText[13] = "加载中...";
            //outtextxy(500, 360, loadingText);

            
        }
        draw();

        EndBatchDraw();
        Sleep(16);
    }
}