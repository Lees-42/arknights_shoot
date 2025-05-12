// player.cpp
#include "player.h"

void player::update() {
    if (get_velocity().x != 0) {  // �ƶ�ʱ����֡
        frame_timer++;
        if (frame_timer >= frame_delay) {
            current_frame = (current_frame + 1) % frame_count;  // ѭ������
            frame_timer = 0;
        }
    }
    else {
        current_frame = 0;  // ��ֹʱ����Ϊ��0֡
    }
}


//void player::shoot(float current_time) {
//    // ���㷢��λ�ã�x: ���ģ�y: �ײ���
//    Vector2 fire_pos = {
//        get_pos().x + get_size().x / 2,
//        get_pos().y + get_size().y / 2
//    };
//    m_weapon.fire(fire_pos, current_time);
//}