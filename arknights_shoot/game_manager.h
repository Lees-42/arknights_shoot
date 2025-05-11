// game_manager.h
#pragma once
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "physics_engine.h"
#include "resource_manage.h"
#include <vector>
#include <graphics.h>



enum game_state { LOADING, MENU, RUNNING, PAUSED, GAME_OVER };

class game_manager {
    game_state m_state;       // ��Ϸ״̬
    map m_game_map;           // ��Ϸ��ͼʵ����1280x720��
    player m_player;          // ���ʵ��
    physics_engine m_physics; // ��������ʵ��
    bool resources_loaded;
    std::vector<enemy> m_enemies;  // ��������

public:
        game_manager():
        m_state(LOADING),
        m_game_map(1280, 720),
        m_player(600, 0) {  // ��ҳ�ʼλ��
        // ��ʼ������
        m_enemies.emplace_back(800,0);  // ����1
    }

    void run();

private:
    void process_input();  // ���봦����cppʵ�֣�
    void update();         // ��Ϸ�߼�����
    void draw();           // ��������Ԫ��
};