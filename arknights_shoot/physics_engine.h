// physics_engine.h
#pragma once
#include "character.h"
#include "map.h"
#include "math_utils.h"
#include "bullet.h"
#include "enemy.h"

class physics_engine {
public:
    static constexpr float GRAVITY = 0.6f;       // �������ٶ�
    static constexpr float MAX_FALL_SPEED = 12;  // ��������ٶ�
    static constexpr float FOOT_HEIGHT = 10.0f;   // �Ų���ײ����߶ȣ��ɵ�����

    void apply_gravity(character& obj);                // Ӧ������
    bool check_platform_collision(character& obj, const map& game_map); // ƽ̨��ײ���
    bool check_bullet_enemy_collision(const bullet& b, const enemy& e);  // �ӵ�-������ײ���
    bool check_map_bounds(const character& obj, const map& game_map);   // ��ͼ�߽���
};

