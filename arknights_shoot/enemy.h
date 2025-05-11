// enemy.h
#pragma once
#include "character.h"
#include "resource_manage.h"

class enemy : public character {
    bool is_alive = true;  // �����Ƿ���
    float speed = 1.0f;  // �����ٶ�
public:
    enemy(float x, float y) : character(x, y, 64, 64) {
        // ��ʼ��������Դ��ʾ����
        resource_manage::get_instance().load_image("enemy_idle", "./res/chars/move_02.png");
    }

    void update() override {  // ���˸����߼���ʾ�����������ƶ���
        if (!is_alive) return;
    }

    void draw() override {  // ���Ƶ���
        IMAGE* img = resource_manage::get_instance().get_image("enemy_idle");
        if (img) putimage((int)pos.x, (int)pos.y, (int)size.x, (int)size.y, img, 0, 0);
    }

    void apply_knockback(float force, float direction) {  // direction: ��1�����˷���
        if (is_alive) {
            // ���ӻ����ٶȣ������� direction ������
            set_velocity_x(get_velocity().x + force * direction);
        }
    }

    bool get_alive() const{return is_alive;}
    void set_alive(bool alive){is_alive = alive;}
};