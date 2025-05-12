// physics_engine.h
#pragma once
#include "character.h"
#include "map.h"
#include "math_utils.h"
#include "bullet.h"
#include "enemy.h"

class physics_engine {
public:
    static constexpr float GRAVITY = 0.6f;       // 重力加速度
    static constexpr float MAX_FALL_SPEED = 12;  // 最大下落速度
    static constexpr float FOOT_HEIGHT = 10.0f;   // 脚部碰撞区域高度（可调整）

    void apply_gravity(character& obj);                // 应用重力
    bool check_platform_collision(character& obj, const map& game_map); // 平台碰撞检测
    bool check_bullet_enemy_collision(const bullet& b, const enemy& e);  // 子弹-敌人碰撞检测
    bool check_map_bounds(const character& obj, const map& game_map);   // 地图边界检测
};

