// character.h
#pragma once
#include "math_utils.h"

class character {
protected:
    Vector2 pos;        // ��ɫλ�ã����Ͻ����꣩
    Vector2 velocity;   // �ٶ�����
    Vector2 size;       // ��ɫ�ߴ磨��ߣ�
    bool is_grounded;   // �Ƿ�վ��ƽ̨��
    float jump_power;   // ��Ծ����
    float friction = 0.9f;  // Ħ��ϵ����0~1��ֵԽ�����Խ����
    float min_velocity = 0.1f;  // ��С�ٶ���ֵ��С�ڴ�ֵʱ�ٶ���0��
    float acceleration = 2.0f;  // ˮƽ���ٶȣ�ÿ�����ӵ��ٶȣ�
    float max_speed = 5.0f;     // ���ˮƽ�ƶ��ٶȣ������ٶ����ޣ�
public:
    character(float x, float y, float w, float h)
        : pos({ x, y }), size({ w, h }), is_grounded(false), jump_power(-15) {
    }
        

    virtual void update() = 0;       // �������ʵ�ֵĸ����߼�
    virtual void draw() = 0;         // ���ƽ�ɫ
    void jump() {                    // ��Ծ����
        if (is_grounded) {
            velocity.y = jump_power;
            is_grounded = false;
        }
    }

    // ������
    /// λ�ýӿڣ��ؼ��Ż����������ã�
    Vector2& get_pos() { return pos; }
    const Vector2& get_pos() const { return pos; }  // ֻ���汾

    // �ߴ�ӿڣ�ֻ�����������ã�
    const Vector2& get_size() const { return size; }

    // �ٶȽӿڣ�����ֱ���޸ģ�
    const Vector2& get_velocity() const { return velocity; }  // ֻ��
    void set_velocity(const Vector2& new_velocity) {          // ��ȫ�޸�
        velocity = new_velocity;
    }
    // ��ѡ��ϸ�����޸��ٶȷ���������Ҫ��
    void set_velocity_x(float x) { velocity.x = x; }
    void set_velocity_y(float y) { velocity.y = y; }

    // ����״̬�ӿ�
    bool get_is_grounded() const { return is_grounded; }
    void set_is_grounded(bool grounded) { is_grounded = grounded; }

    // ��Ծ���Ƚӿڣ���ѡ��̬������
    float get_jump_power() const { return jump_power; }
    void set_jump_power(float power) { jump_power = power; }

    // Ħ��ϵ���ӿڣ���ѡ��̬������
    void set_friction(float f) { friction = f; }
    float get_friction() const { return friction; }


    friend class physics_engine;
};