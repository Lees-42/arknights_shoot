// player.h
#pragma once
#include "character.h"
#include "weapon.h"
#include <vector>


class player : public character {
    weapon m_weapon;  // 玩家武器

public:
    player(float x, float y) : character(x, y, 64, 64) {
        // 加载角色资源（示例路径）
        resource_manage::get_instance().load_image("player_idle", "./res/chars/move_02.png");
    }

    void update() override;  // 实现基类纯虚函数
    void draw() override {
        IMAGE* img = resource_manage::get_instance().get_image("player_idle");
        if (img) {
            // 缩放图片到角色的 size（64x96）
            putimage((int)pos.x, (int)pos.y,
                (int)size.x, (int)size.y,  // 目标宽度、高度（角色尺寸）
                img, 0, 0);  // 原图的起点（0,0）
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