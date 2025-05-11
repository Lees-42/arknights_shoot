// player.h
#pragma once
#include "character.h"
#include "weapon.h"
#include <vector>


class player : public character {
    weapon m_weapon;  // �������

public:
    player(float x, float y) : character(x, y, 64, 64) {
        // ���ؽ�ɫ��Դ��ʾ��·����
        resource_manage::get_instance().load_image("player_idle", "./res/chars/move_02.png");
    }

    void update() override;  // ʵ�ֻ��ി�麯��
    void draw() override {
        IMAGE* img = resource_manage::get_instance().get_image("player_idle");
        if (img) {
            // ����ͼƬ����ɫ�� size��64x96��
            putimage((int)pos.x, (int)pos.y,
                (int)size.x, (int)size.y,  // Ŀ���ȡ��߶ȣ���ɫ�ߴ磩
                img, 0, 0);  // ԭͼ����㣨0,0��
        }

    }
    
    void shoot(float current_time) {
        // ���������λ�÷��䣨x: ���ң�y: ���£�
        Vector2 fire_pos = {
            pos.x + size.x / 2,
            pos.y + size.y / 2
        };
        m_weapon.fire(fire_pos, current_time);
    }

    weapon& getWeapon() { return m_weapon; }
    const weapon& getWeapon() const { return m_weapon; }
};