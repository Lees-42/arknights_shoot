// player.h
#pragma once
#include "character.h"
#include "weapon.h"
#include <vector>


class player : public character {
    weapon m_weapon;  // �������
    int current_frame;  // ��ǰ֡
    int frame_count;    // ��֡��
    int frame_delay;    // ֡�ӳ�
    int frame_timer;    // ֡��ʱ��

public:
    player(float x, float y) : character(x, y, 64, 113), frame_count(33) {
        // ���ؽ�ɫ��Դ��ʾ��·����
        resource_manage::get_instance().load_image("player_idle_right", "./res/chars/walk_right_1.png");
        resource_manage::get_instance().load_image("player_idle_left", "./res/chars/walk_left_1.png");
        // ���ؽ�ɫ��������֡ͼƬ
        resource_manage::get_instance().load_image_sequence("player_walk_right_", "./res/chars/move/walk_right/walk_right_", frame_count);
        resource_manage::get_instance().load_image_sequence("player_walk_left_", "./res/chars/move/walk_left/walk_left_", frame_count);
    }

    void update() override;  // ʵ�ָ����߼�
    void draw() {
        IMAGE* img = nullptr;
        if (get_velocity().x != 0) {  // �����ɫ���ƶ�
            if (get_facing_right()) {
                std::string key = "player_walk_right_" + std::to_string(current_frame);
                img = resource_manage::get_instance().get_image(key);
            }
            else {
                std::string key = "player_walk_left_" + std::to_string(current_frame);
                img = resource_manage::get_instance().get_image(key);
            }
        }
        else {  // �����ɫ��ֹ
            if (get_facing_right()) {
                img = resource_manage::get_instance().get_image("player_idle_right");
            }
            else {
                img = resource_manage::get_instance().get_image("player_idle_left");
            }
        }

        if (img) {
            putimage((int)get_pos().x, (int)get_pos().y,
                (int)get_size().x, (int)get_size().y,  // Ŀ��ߴ磨��ɫ��С��
                img, 0, 0);                // ��ͼƬԭ��(0,0)��ʼ����
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