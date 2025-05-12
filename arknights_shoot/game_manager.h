// game_manager.h
#pragma once
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "physics_engine.h"
#include "resource_manage.h"
#include <vector>
#include <graphics.h>
#include <random>


enum game_state { LOADING, MENU, RUNNING, PAUSED, GAME_OVER };

class game_manager {
    game_state m_state;       // 游戏状态
    map m_game_map;           // 游戏地图实例（1280x720）
    player m_player;          // 玩家实例
    physics_engine m_physics; // 物理引擎实例
    bool resources_loaded;
    std::vector<enemy> m_enemies;  // 敌人数组
    float m_enemy_spawn_timer = 0.0f;    // 生成计时器（记录距上次生成的时间）
    float m_enemy_spawn_interval = 5.0f; // 生成间隔（每5秒尝试生成）
    std::mt19937 m_rng;                  // 随机数生成器（更安全）
public:
    game_manager() : m_state(LOADING), m_game_map(1280, 720), m_player(400, 0) {
        // 初始化随机数种子（用当前时间）
        std::random_device rd;
        m_rng.seed(rd());
        // 初始化敌人
        m_enemies.emplace_back(800,0);  
    }
    int get_alive_enemy_count()const;
    void run();

private:
    void process_input();  // 输入处理（见cpp实现）
    void update();         // 游戏逻辑更新
    void draw();           // 绘制所有元素
};