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

        // 检测脚部区域与平台的碰撞
        if (IntersectRect(&intersect, &char_foot_rect, &plat_rect)) {
            // 仅当角色处于下落状态时才处理碰撞
            if (obj.get_velocity().y > 0) {
                // 记录最高的平台顶部Y坐标
                if (plat_rect.top > highest_platform_top) {
                    highest_platform_top = plat_rect.top;
                }
            }
        }
    }

    // 存在有效碰撞时调整角色位置
    if (highest_platform_top != -FLT_MAX) {
        obj.get_pos().y = highest_platform_top - obj.get_size().y;  // 角色底部对齐平台顶部
        obj.set_velocity_y(0);  // 垂直速度归零
        obj.set_is_grounded(true);  // 标记为站在平台上
        return true;
    }
    // 无碰撞时，角色未站在平台上
    obj.set_is_grounded(false);
    return false;
}
bool physics_engine::check_map_bounds(const character& obj, const map& game_map) {
    // 检测X轴左右边界 + Y轴上下边界（如掉出屏幕底部）
    const float obj_bottom = obj.get_pos().y + obj.get_size().y;  // 角色底部Y坐标
    return (
        obj.get_pos().x < 0 ||                          // 左边界
        obj.get_pos().x + obj.get_size().x > game_map.get_width() ||  // 右边界
        obj.get_pos().y < 0 ||                          // 上边界（如跳出台面）
        obj_bottom > game_map.get_height()              // 下边界（掉出屏幕底部）
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
    return IntersectRect(&intersect, &bullet_rect, &enemy_rect);  // AABB碰撞检测
}