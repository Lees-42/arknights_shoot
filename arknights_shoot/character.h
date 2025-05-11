// character.h
#pragma once
#include "math_utils.h"

class character {
protected:
    Vector2 pos;        // 角色位置（左上角坐标）
    Vector2 velocity;   // 速度向量
    Vector2 size;       // 角色尺寸（宽高）
    bool is_grounded;   // 是否站在平台上
    float jump_power;   // 跳跃力度
    float friction = 0.9f;  // 摩擦系数（0~1，值越大减速越慢）
    float min_velocity = 0.1f;  // 最小速度阈值（小于此值时速度置0）
    float acceleration = 2.0f;  // 水平加速度（每秒增加的速度）
    float max_speed = 5.0f;     // 最大水平移动速度（限制速度上限）
public:
    character(float x, float y, float w, float h)
        : pos({ x, y }), size({ w, h }), is_grounded(false), jump_power(-15) {
    }
        

    virtual void update() = 0;       // 子类必须实现的更新逻辑
    virtual void draw() = 0;         // 绘制角色
    void jump() {                    // 跳跃方法
        if (is_grounded) {
            velocity.y = jump_power;
            is_grounded = false;
        }
    }

    // 访问器
    /// 位置接口（关键优化：返回引用）
    Vector2& get_pos() { return pos; }
    const Vector2& get_pos() const { return pos; }  // 只读版本

    // 尺寸接口（只读，返回引用）
    const Vector2& get_size() const { return size; }

    // 速度接口（限制直接修改）
    const Vector2& get_velocity() const { return velocity; }  // 只读
    void set_velocity(const Vector2& new_velocity) {          // 安全修改
        velocity = new_velocity;
    }
    // 可选：细粒度修改速度分量（若需要）
    void set_velocity_x(float x) { velocity.x = x; }
    void set_velocity_y(float y) { velocity.y = y; }

    // 地面状态接口
    bool get_is_grounded() const { return is_grounded; }
    void set_is_grounded(bool grounded) { is_grounded = grounded; }

    // 跳跃力度接口（可选动态调整）
    float get_jump_power() const { return jump_power; }
    void set_jump_power(float power) { jump_power = power; }

    // 摩擦系数接口（可选动态调整）
    void set_friction(float f) { friction = f; }
    float get_friction() const { return friction; }


    friend class physics_engine;
};