// weapon.h
#pragma once
#include "bullet.h"
#include <vector>
#include <chrono>

class weapon {
    std::vector<bullet> m_bullets;  // �ӵ��б�
    float fire_interval = 0.1f;     // ���������룩
    float last_fire_time = 0.0f;    // �ϴ����ʱ��

public:
    // �����ӵ�����ָ��λ�ã�������������
    void fire(const Vector2& fire_pos, float current_time, float speed_x) {  // ����speed_x����
        if (current_time - last_fire_time >= fire_interval) {
            m_bullets.emplace_back(fire_pos.x, fire_pos.y, speed_x);  // ��̬�ٶȷ���
            last_fire_time = current_time;
        }
    }

    // �����ӵ�״̬���ƶ����Ƴ�ʧЧ�ӵ���
    void update(float delta_time) {
        for (auto& b : m_bullets) {
            b.update( delta_time);  // �ӵ�������£��ƶ�������飩
        }
        // �Ƴ��������ӵ���ʹ���㷨������
        m_bullets.erase(
            std::remove_if(m_bullets.begin(), m_bullets.end(),
                [](const bullet& b) { return !b.get_alive(); }),
            m_bullets.end()
        );
    }

    // �������д���ӵ�
    void draw() {
        for (const auto& b : m_bullets) {
            b.draw();
        }
    }

    // ֻ�������ӵ��б�������ײ��⣩
    const std::vector<bullet>& get_bullets() const { return m_bullets; }
};