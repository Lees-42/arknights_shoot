// player.h
#pragma once
#include "character.h"
#include "weapon.h"
#include <vector>
#include "graphics_utils.h"
#pragma comment(lib, "MSIMG32.LIB ")
class player : public character {
    weapon m_weapon;  // �������
    int current_frame;  // ��ǰ֡
    int frame_count;    // ��֡��
    int frame_delay;    // ֡�ӳ�
    int frame_timer;    // ֡��ʱ��

public:
    
    player(float x, float y) : character(x, y, 64, 100), frame_count(33) {
        // ���ؽ�ɫ��Դ��ʾ��·����
        resource_manage::get_instance().load_image("player_idle_right", "./res/chars/walk_right_1.png");
        resource_manage::get_instance().load_image("player_idle_left", "./res/chars/walk_right_2.png");
        // ���ؽ�ɫ��������֡ͼƬ
        resource_manage::get_instance().load_image_sequence("player_walk_right_", "./res/chars/move1/walk_right/walk_right_", frame_count);
        resource_manage::get_instance().load_image_sequence("player_walk_left_", "./res/chars/move1/walk_left/walk_right_", frame_count);
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
            putimage_alpha(
                (int)get_pos().x,
                (int)get_pos().y,
                (int)get_size().x,  // Ŀ���ȣ���ɫ��ȣ�
                (int)get_size().y,  // Ŀ��߶ȣ���ɫ�߶ȣ�
                img
            );
        }
    }
    void shoot(float current_time) {
        // ��ȡ��ɫ��ǰ����
        bool facing_right = get_facing_right();
        float direction = facing_right ? 1.0f : -1.0f;  // ����Ϊ1������Ϊ-1

        // �����ӵ��ٶȣ������ɳ��������
        float bullet_speed = 300.0f;  // �ӵ������ٶȣ��ɵ�����
        float speed_x = bullet_speed * direction;

        // �����ӵ�����λ�ã�����ӽ�ɫ�����ڲ����ɣ�
        float fire_x = pos.x + (facing_right ? (size.x - 10) : 10);  // ����ʱ�ӽ�ɫ�Ҳ෢�䣬����ʱ����ࣨƫ��10���أ�
        float fire_y = pos.y + size.y / 2;  // ��ֱ�������

        Vector2 fire_pos = { fire_x, fire_y };

        // ���������෢���ӵ������ݷ����ٶȣ�
        m_weapon.fire(fire_pos, current_time, speed_x);
    }

    weapon& getWeapon() { return m_weapon; }
    const weapon& getWeapon() const { return m_weapon; }
};