// map.h
#pragma once
#include <vector>
#include "resource_manage.h"
#include "math_utils.h"


struct platform {
    RECT rect;  // ƽ̨��������
    IMAGE* img; // ƽ̨ͼƬ������Դ�����ȡ��

    platform(int x, int y) {
        img = resource_manage::get_instance().get_image("platform");
        if (img) {
            // ��ͼƬ��ȡʵ�ʿ�Ⱥ͸߶�
            int w = img->getwidth();
            int h = img->getheight();
            rect = { x, y, x + w, y + h };  // ��̬���� rect
        }
        else {
            // ͼƬ����ʧ��ʱ��Ĭ��ֵ������ʵ�����������
            rect = { x, y, x + 100, y + 20 };
        }
    }
    RECT get_rect() const { return rect; }
    void draw() {
        putimage(rect.left, rect.top, img);
    }
};

class map {
    std::vector<platform> m_platforms;  // ƽ̨�б�
    int m_width;                        // ��ͼ�ܿ��
    int m_height;                       // ��ͼ�ܸ߶�

public:
    map(int width, int height) : m_width(width),m_height(height) {
        resource_manage::get_instance().load_image("platform", "./res/platforms/1.png");
        // ��ʼ�����������ƽ̨��ÿ���������
        m_platforms.emplace_back(240, 500); 
        m_platforms.emplace_back(240, 350);  
        m_platforms.emplace_back(240, 200);  
        m_platforms.emplace_back(800, 200);
        m_platforms.emplace_back(800, 350); 
        m_platforms.emplace_back(800, 500);

        // ����ƽ̨��Դ������Ϸ��ʼ��ʱ���ã�
        
    }

    void draw() {  // ���Ƶ�ͼ��ƽ̨
        IMAGE* bg_img = resource_manage::get_instance().get_image("game_map");
        if (bg_img) {
            putimage(0, 0, bg_img);
        }
        else {
            // ����ͼƬ����ʧ��ʱ��Ĭ��ֵ������ʵ�����������
            setbkcolor(RGB(0x00, 0x00, 0x00));
            cleardevice();
        }
        for (auto& p : m_platforms) p.draw();
    }

    const std::vector<platform>& get_platforms() const { return m_platforms; }
    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
};