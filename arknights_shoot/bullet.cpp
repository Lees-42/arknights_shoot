#include "bullet.h"
//#include "player.h"
//
//Bullet::Bullet() : x(0), y(0), vx(0), vy(0), impact_force(0), damage(0), width(0), height(0), existing_time(0), is_existing(false), is_gravity(false) {}
//
//void Bullet::update() {
//    if (is_existing) {
//        if (is_gravity) {
//            vy += 0.06;
//        }
//        x += vx;
//        y += vy;
//        if (existing_time > 0) {
//            existing_time--;
//        }
//        if (x >= 1440 || x <= -1440 || existing_time == 0) {
//            is_existing = false;
//        }
//    }
//}
//
//void Bullet::action(Player* player) {
//    if (vx > 0)
//        player->ax += impact_force;
//    else {
//        player->ax -= impact_force;
//    }
//    player->health -= damage;
//    is_existing = false;
//    // ����ȱ���������ţ�EasyX û��ֱ��֧�֣��ɺ�����չ
//}
//
//void Bullet::draw() {
//    if (is_existing) {
//        setfillcolor(RGB(255, 164, 0));
//        fillrectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + width), static_cast<int>(y + height));
//    }
//}