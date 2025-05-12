// game_manager.h
#pragma once
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "physics_engine.h"
#include "resource_manage.h"
#include <vector>
#include <graphics.h>
#include <random>


enum game_state { LOADING, MENU, RUNNING, PAUSED, GAME_OVER };

class game_manager {
    game_state m_state;       // ��Ϸ״̬
    map m_game_map;           // ��Ϸ��ͼʵ����1280x720��
    player m_player;          // ���ʵ��
    physics_engine m_physics; // ��������ʵ��
    bool resources_loaded;
    std::vector<enemy> m_enemies;  // ��������
    float m_enemy_spawn_timer = 0.0f;    // ���ɼ�ʱ������¼���ϴ����ɵ�ʱ�䣩
    float m_enemy_spawn_interval = 5.0f; // ���ɼ����ÿ5�볢�����ɣ�
    std::mt19937 m_rng;                  // �����������������ȫ��
public:
    game_manager() : m_state(LOADING), m_game_map(1280, 720), m_player(400, 0) {
        // ��ʼ����������ӣ��õ�ǰʱ�䣩
        std::random_device rd;
        m_rng.seed(rd());
        // ��ʼ������
        m_enemies.emplace_back(800,0);  
    }
    int get_alive_enemy_count()const;
    void run();

private:
    void process_input();  // ���봦����cppʵ�֣�
    void update();         // ��Ϸ�߼�����
    void draw();           // ��������Ԫ��
};