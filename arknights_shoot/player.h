// player.h
#pragma once
#include "character.h"
#include "weapon.h"
#include <vector>


class player : public character {
    weapon m_weapon;  // 玩家武器
    int current_frame;  // 当前帧
    int frame_count;    // 总帧数
    int frame_delay;    // 帧延迟
    int frame_timer;    // 帧计时器

public:
    player(float x, float y) : character(x, y, 64, 113), frame_count(33) {
        // 加载角色资源（示例路径）
        resource_manage::get_instance().load_image("player_idle_right", "./res/chars/walk_right_1.png");
        resource_manage::get_instance().load_image("player_idle_left", "./res/chars/walk_left_1.png");
        // 加载角色行走序列帧图片
        resource_manage::get_instance().load_image_sequence("player_walk_right_", "./res/chars/move/walk_right/walk_right_", frame_count);
        resource_manage::get_instance().load_image_sequence("player_walk_left_", "./res/chars/move/walk_left/walk_left_", frame_count);
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
            putimage((int)get_pos().x, (int)get_pos().y,
                (int)get_size().x, (int)get_size().y,  // 目标尺寸（角色大小）
                img, 0, 0);                // 从图片原点(0,0)开始绘制
        }
    }
    void shoot(float current_time) {
        // 从玩家中心位置发射（x: 中右，y: 中下）
        Vector2 fire_pos = {
            pos.x + size.x / 2,
            pos.y + size.y / 2
        };
        m_weapon.fire(fire_pos, current_time);
    }

    weapon& getWeapon() { return m_weapon; }
    const weapon& getWeapon() const { return m_weapon; }
};