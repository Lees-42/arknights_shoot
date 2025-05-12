// enemy.h
#pragma once
#include "character.h"
#include "resource_manage.h"

class enemy : public character {
    bool is_alive = true;  // 敌人是否存活
    float speed = 1.0f;  // 敌人速度
public:
    enemy(float x, float y) : character(x, y, 64, 64) {
        // 初始化敌人资源（示例）
        resource_manage::get_instance().load_image("enemy_idle_right", "./res/chars/move_02_right.png");
    resource_manage::get_instance().load_image("enemy_idle_left", "./res/chars/move_02_left.png");
    }

    void update() override {  // 敌人更新逻辑（示例：简单左右移动）
        if (!is_alive) return;
    }

    void draw() override {  // 绘制敌人
        IMAGE* img = nullptr;
        if (get_facing_right()) {
            img = resource_manage::get_instance().get_image("enemy_idle_right");
        }
        else {
            img = resource_manage::get_instance().get_image("enemy_idle_left");
        }
        if (img) {
            putimage((int)pos.x, (int)pos.y,
                (int)size.x, (int)size.y,  // 目标尺寸（敌人大小）
                img, 0, 0);  // 直接使用预加载的方向图片
        }
    }

    void apply_knockback(float force, float direction) {  // direction: ±1（击退方向）
        if (is_alive) {
            // 叠加击退速度（方向由 direction 决定）
            set_velocity_x(get_velocity().x + force * direction);
        }
    }

    bool get_alive() const{return is_alive;}
    void set_alive(bool alive){is_alive = alive;}
};