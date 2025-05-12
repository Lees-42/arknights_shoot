// bullet.h
#pragma once
#include "resource_manage.h"
#include "math_utils.h"

class bullet {
    Vector2 pos;        // �ӵ�λ��
    Vector2 velocity;   // �ӵ��ٶ�
    mutable bool is_alive;      // ���״̬
    float knockback;    // ��������
    float lifetime;     // �����ʱ�䣨�룩
    float alive_time;   // �Ѵ��ʱ�䣨�룩

public:
    // ���캯������ʼ��λ�á��ٶȣ�������Դ
    bullet(float x, float y, float speed_x)
        : pos({ x, y }), velocity({ speed_x, 0 }),
        is_alive(true), knockback(5.0f),
        lifetime(10.0f), alive_time(0.0f) {
        resource_manage::get_instance().load_image("bullet", "./res/bullets/2.png");
    }

    

    // �����ӵ�״̬���ƶ������ʱ�䣩
    void update(float delta_time) {
        if (!is_alive) return;

        // ˮƽ�ƶ�����������������չΪ�����ߣ�
        pos.x += velocity.x * delta_time;
        alive_time += delta_time;

        // ������Ļ����ʱ�������ʧЧ
        if (pos.x < 0 || pos.x > 1280 || alive_time >= lifetime) {
            is_alive = false;
        }
    }

    // �����ӵ��������ʱ���ƣ�
    void draw() const {
        if (!is_alive) return;

        IMAGE* img = resource_manage::get_instance().get_image("bullet");
        if (img) {
            putimage((int)pos.x, (int)pos.y, img);
        }
    }

    

    // ��ײ�����ڼ������˵���ײ��
    RECT get_rect() const {
        IMAGE* img = resource_manage::get_instance().get_image("bullet");
        if (img) {
            return {
                (long)pos.x, (long)pos.y,
                (long)(pos.x + img->getwidth()),
                (long)(pos.y + img->getheight())
            };
        }
        // ����Դʱʹ��Ĭ����ײ��20x10��
        return { (long)pos.x, (long)pos.y, (long)(pos.x + 20), (long)(pos.y + 10) };
    }

    // ���״̬�ӿ�
    bool get_alive() const { return is_alive; }

    // �������Ƚӿ�
    float get_knockback() const { return knockback; 
    }

    // ��������ȡ�ӵ��ٶȣ������жϷ���
    const Vector2& get_velocity() const { return velocity; }

    // ���������ô��״̬�����ڱ�ǻ��к����٣�
    void set_alive(bool alive) const { is_alive = alive; }
};