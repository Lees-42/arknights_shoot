// player.cpp
#include "player.h"

void player::update() {
    if (get_velocity().x != 0) {  // 移动时更新帧
        frame_timer++;
        if (frame_timer >= frame_delay) {
            current_frame = (current_frame + 1) % frame_count;  // 循环播放
            frame_timer = 0;
        }
    }
    else {
        current_frame = 0;  // 静止时重置为第0帧
    }
}


//void player::shoot(float current_time) {
//    // 计算发射位置（x: 中心，y: 底部）
//    Vector2 fire_pos = {
//        get_pos().x + get_size().x / 2,
//        get_pos().y + get_size().y / 2
//    };
//    m_weapon.fire(fire_pos, current_time);
//}