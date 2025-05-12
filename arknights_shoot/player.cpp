// player.cpp
#include "player.h"

void player::update() {

    apply_friction();

    if (get_velocity().x != 0) {  // �ƶ�ʱ����֡
        frame_timer++;
        if (frame_timer >= frame_delay) {
            current_frame = (current_frame + 1) % frame_count;  // ѭ������
            frame_timer = 0;
        }
    }
    else {
        current_frame = 0;  // ��ֹʱ����Ϊ��0֡
        frame_timer = 0;
    }
}


