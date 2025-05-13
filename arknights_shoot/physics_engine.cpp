// physics_engine.cpp
#include "physics_engine.h"
#include "map.h"
#include "character.h"
#include <algorithm>
#include <windows.h>
void physics_engine::apply_gravity(character& obj) {
    // ��Ϊͨ�� set_velocity_y �޸��ٶ�
    obj.set_velocity_y(obj.get_velocity().y + GRAVITY);
    if (obj.get_velocity().y > MAX_FALL_SPEED) {
        obj.set_velocity_y(MAX_FALL_SPEED);
    }
}

bool physics_engine::check_platform_collision(character& obj, const map& game_map) {

    float highest_platform_top = -FLT_MAX;


    RECT char_foot_rect = {
        (long)obj.get_pos().x,
        (long)(obj.get_pos().y + obj.get_size().y - FOOT_HEIGHT),
        (long)(obj.get_pos().x + obj.get_size().x),
        (long)(obj.get_pos().y + obj.get_size().y)
    };

    for (const auto& platform : game_map.get_platforms()) {
        RECT plat_rect = platform.get_rect();
        RECT intersect;

        // ���Ų�������ƽ̨����ײ
        if (IntersectRect(&intersect, &char_foot_rect, &plat_rect)) {
            // ������ɫ��������״̬ʱ�Ŵ�����ײ
            if (obj.get_velocity().y > 0) {
                // ��¼��ߵ�ƽ̨����Y����
                if (plat_rect.top > highest_platform_top) {
                    highest_platform_top = plat_rect.top;
                }
            }
        }
    }

    // ������Ч��ײʱ������ɫλ��
    if (highest_platform_top != -FLT_MAX) {
        obj.get_pos().y = highest_platform_top - obj.get_size().y;  // ��ɫ�ײ�����ƽ̨����
        obj.set_velocity_y(0);  // ��ֱ�ٶȹ���
        obj.set_is_grounded(true);  // ���Ϊվ��ƽ̨��
        return true;
    }
    // ����ײʱ����ɫδվ��ƽ̨��
    obj.set_is_grounded(false);
    return false;
}
bool physics_engine::check_map_bounds(const character& obj, const map& game_map) {
    // ���X�����ұ߽� + Y�����±߽磨�������Ļ�ײ���
    const float obj_bottom = obj.get_pos().y + obj.get_size().y;  // ��ɫ�ײ�Y����
    return (
        obj.get_pos().x < 0 ||                          // ��߽�
        obj.get_pos().x + obj.get_size().x > game_map.get_width() ||  // �ұ߽�
        obj.get_pos().y < 0 ||                          // �ϱ߽磨������̨�棩
        obj_bottom > game_map.get_height()              // �±߽磨������Ļ�ײ���
        );
}

bool physics_engine::check_bullet_enemy_collision(const bullet& b, const enemy& e) {
    RECT bullet_rect = b.get_rect();
    RECT enemy_rect = {
        (long)e.get_pos().x,
        (long)e.get_pos().y,
        (long)(e.get_pos().x + e.get_size().x),
        (long)(e.get_pos().y + e.get_size().y)
    };
    RECT intersect;
    return IntersectRect(&intersect, &bullet_rect, &enemy_rect);  // AABB��ײ���
}