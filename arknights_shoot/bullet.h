// bullet.h
#pragma once
#include "resource_manage.h"
#include "math_utils.h"

class bullet {
    Vector2 pos;        // 子弹位置
    Vector2 velocity;   // 子弹速度
    mutable bool is_alive;      // 存活状态
    float knockback;    // 击退力度
    float lifetime;     // 最大存活时间（秒）
    float alive_time;   // 已存活时间（秒）

public:
    // 构造函数：初始化位置、速度，加载资源
    bullet(float x, float y, float speed_x)
        : pos({ x, y }), velocity({ speed_x, 0 }),
        is_alive(true), knockback(5.0f),
        lifetime(10.0f), alive_time(0.0f) {
        resource_manage::get_instance().load_image("bullet", "./res/bullets/2.png");
    }

    

    // 更新子弹状态（移动、存活时间）
    void update(float delta_time) {
        if (!is_alive) return;

        // 水平移动（忽略重力，可扩展为抛物线）
        pos.x += velocity.x * delta_time;
        alive_time += delta_time;

        // 超出屏幕或存活时间过长则失效
        if (pos.x < 0 || pos.x > 1280 || alive_time >= lifetime) {
            is_alive = false;
        }
    }

    // 绘制子弹（仅存活时绘制）
    void draw() const {
        if (!is_alive) return;

        IMAGE* img = resource_manage::get_instance().get_image("bullet");
        if (img) {
            putimage((int)pos.x, (int)pos.y, img);
        }
    }

    

    // 碰撞框（用于检测与敌人的碰撞）
    RECT get_rect() const {
        IMAGE* img = resource_manage::get_instance().get_image("bullet");
        if (img) {
            return {
                (long)pos.x, (long)pos.y,
                (long)(pos.x + img->getwidth()),
                (long)(pos.y + img->getheight())
            };
        }
        // 无资源时使用默认碰撞框（20x10）
        return { (long)pos.x, (long)pos.y, (long)(pos.x + 20), (long)(pos.y + 10) };
    }

    // 存活状态接口
    bool get_alive() const { return is_alive; }

    // 击退力度接口
    float get_knockback() const { return knockback; 
    }

    // 新增：获取子弹速度（用于判断方向）
    const Vector2& get_velocity() const { return velocity; }

    // 新增：设置存活状态（用于标记击中后销毁）
    void set_alive(bool alive) const { is_alive = alive; }
};