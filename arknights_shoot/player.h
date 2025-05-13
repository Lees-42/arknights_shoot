// player.h
#pragma once
#include "character.h"
#include "weapon.h"
#include <vector>
#include "graphics_utils.h"
#pragma comment(lib, "MSIMG32.LIB ")
class player : public character {
    weapon m_weapon;  // 玩家武器
    int current_frame;  // 当前帧
    int frame_count;    // 总帧数
    int frame_delay;    // 帧延迟
    int frame_timer;    // 帧计时器

public:
    
    player(float x, float y) : character(x, y, 64, 100), frame_count(33) {
        // 加载角色资源（示例路径）
        resource_manage::get_instance().load_image("player_idle_right", "./res/chars/walk_right_1.png");
        resource_manage::get_instance().load_image("player_idle_left", "./res/chars/walk_right_2.png");
        // 加载角色行走序列帧图片
        resource_manage::get_instance().load_image_sequence("player_walk_right_", "./res/chars/move1/walk_right/walk_right_", frame_count);
        resource_manage::get_instance().load_image_sequence("player_walk_left_", "./res/chars/move1/walk_left/walk_right_", frame_count);
    }

    void update() override;  // 实现更新逻辑
    void draw() {
        IMAGE* img = nullptr;
        if (get_velocity().x != 0) {  // 如果角色在移动
            if (get_facing_right()) {
                std::string key = "player_walk_right_" + std::to_string(current_frame);
                img = resource_manage::get_instance().get_image(key);
            }
            else {
                std::string key = "player_walk_left_" + std::to_string(current_frame);
                img = resource_manage::get_instance().get_image(key);
            }
        }
        else {  // 如果角色静止
            if (get_facing_right()) {
                img = resource_manage::get_instance().get_image("player_idle_right");
            }
            else {
                img = resource_manage::get_instance().get_image("player_idle_left");
            }
        }

        if (img) {
            putimage_alpha(
                (int)get_pos().x,
                (int)get_pos().y,
                (int)get_size().x,  // 目标宽度（角色宽度）
                (int)get_size().y,  // 目标高度（角色高度）
                img
            );
        }
    }
    void shoot(float current_time) {
        // 获取角色当前朝向
        bool facing_right = get_facing_right();
        float direction = facing_right ? 1.0f : -1.0f;  // 向右为1，向左为-1

        // 计算子弹速度（方向由朝向决定）
        float bullet_speed = 300.0f;  // 子弹基础速度（可调整）
        float speed_x = bullet_speed * direction;

        // 调整子弹发射位置（避免从角色身体内部生成）
        float fire_x = pos.x + (facing_right ? (size.x - 10) : 10);  // 向右时从角色右侧发射，向左时从左侧（偏移10像素）
        float fire_y = pos.y + size.y / 2;  // 垂直方向居中

        Vector2 fire_pos = { fire_x, fire_y };

        // 调用武器类发射子弹（传递方向速度）
        m_weapon.fire(fire_pos, current_time, speed_x);
    }

    weapon& getWeapon() { return m_weapon; }
    const weapon& getWeapon() const { return m_weapon; }
};