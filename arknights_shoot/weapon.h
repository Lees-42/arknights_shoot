// weapon.h
#pragma once
#include "bullet.h"
#include <vector>
#include <chrono>

class weapon {
    std::vector<bullet> m_bullets;  // 子弹列表
    float fire_interval = 0.3f;     // 射击间隔（秒）
    float last_fire_time = 0.0f;    // 上次射击时间

public:
    // 发射子弹（从指定位置，考虑射击间隔）
    void fire(const Vector2& fire_pos, float current_time) {
        if (current_time - last_fire_time >= fire_interval) {
            // 发射向右的子弹
            m_bullets.emplace_back(fire_pos.x, fire_pos.y, 100.0f);
            last_fire_time = current_time;  // 更新上次射击时间
        }
    }

    // 更新子弹状态（移动、移除失效子弹）
    void update(float delta_time) {
        for (auto& b : m_bullets) {
            b.update( delta_time);  // 子弹自身更新（移动、存活检查）
        }
        // 移除不存活的子弹（使用算法库清理）
        m_bullets.erase(
            std::remove_if(m_bullets.begin(), m_bullets.end(),
                [](const bullet& b) { return !b.get_alive(); }),
            m_bullets.end()
        );
    }

    // 绘制所有存活子弹
    void draw() {
        for (const auto& b : m_bullets) {
            b.draw();
        }
    }

    // 只读访问子弹列表（用于碰撞检测）
    const std::vector<bullet>& get_bullets() const { return m_bullets; }
};