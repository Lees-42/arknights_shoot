// player.cpp
#include "player.h"

void player::update() {

    apply_friction();

    if (get_velocity().x != 0) {  // 移动时更新帧
        frame_timer++;
        if (frame_timer >= frame_delay) {
            current_frame = (current_frame + 1) % frame_count;  // 循环播放
            frame_timer = 0;
        }
    }
    else {
        current_frame = 0;  // 静止时重置为第0帧
        frame_timer = 0;
    }
}


