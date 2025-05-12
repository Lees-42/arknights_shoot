// physics_engine.cpp
#include "physics_engine.h"
#include "map.h"
#include "character.h"
#include <algorithm>
#include <windows.h>
void physics_engine::apply_gravity(character& obj) {
    // 改为通过 set_velocity_y 修改速度
    obj.set_velocity_y(obj.get_velocity().y + GRAVITY);
    if (obj.get_velocity().y > MAX_FALL_SPEED) {
        obj.set_velocity_y(MAX_FALL_SPEED);
    }
}

bool physics_engine::check_platform_collision(character& obj, const map& game_map) {
    bool collided_vertically = false; // 标记是否发生垂直碰撞（上下方向）
    float highest_platform_top = -FLT_MAX;
    RECT char_rect = {
        (long)obj.get_pos().x,
        (long)obj.get_pos().y,
        (long)(obj.get_pos().x + obj.get_size().x),
        (long)(obj.get_pos().y + obj.get_size().y)
    };

    for (const auto& platform : game_map.get_platforms()) {
        RECT plat_rect = platform.get_rect();
        RECT intersect;

        // 先判断是否有碰撞
        if (!IntersectRect(&intersect, &char_rect, &plat_rect)) {
            continue;
        }

        // 计算x和y方向的重叠量
        int x_overlap = intersect.right - intersect.left;   // x方向重叠宽度
        int y_overlap = intersect.bottom - intersect.top;   // y方向重叠高度

        if (x_overlap >= y_overlap && obj.get_velocity().y > 0) {
            // 记录最高平台顶部
            if (plat_rect.top > highest_platform_top) {
                highest_platform_top = plat_rect.top;
            }
            collided_vertically = true;
        }
    }

    // 处理垂直碰撞：将角色固定在最高平台的顶部
    if (collided_vertically) {
        obj.get_pos().y = highest_platform_top - obj.get_size().y;
        obj.set_velocity_y(0);
        obj.set_is_grounded(true);
        return true;
    }

    // 无垂直碰撞时，角色未站在平台上
    obj.set_is_grounded(false);
    return false;
}
bool physics_engine::check_map_bounds(const character& obj, const map& game_map) {
    // 左右边界检测（超出即淘汰）
    return (obj.get_pos().x < 0 || obj.get_pos().x + obj.get_size().x > game_map.get_width());
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
    return IntersectRect(&intersect, &bullet_rect, &enemy_rect);  // AABB碰撞检测
}