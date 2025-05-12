// map.h
#pragma once
#include <vector>
#include "resource_manage.h"
#include "math_utils.h"


struct platform {
    RECT rect;  // 平台矩形区域
    IMAGE* img; // 平台图片（从资源管理获取）

    platform(int x, int y) {
        img = resource_manage::get_instance().get_image("platform");
        if (img) {
            // 从图片获取实际宽度和高度
            int w = img->getwidth();
            int h = img->getheight();
            rect = { x, y, x + w, y + h };  // 动态计算 rect
        }
        else {
            // 图片加载失败时的默认值（根据实际情况调整）
            rect = { x, y, x + 100, y + 20 };
        }
    }
    RECT get_rect() const { return rect; }
    void draw() {
        putimage(rect.left, rect.top, img);
    }
};

class map {
    std::vector<platform> m_platforms;  // 平台列表
    int m_width;                        // 地图总宽度

public:
    map(int width, int height) : m_width(width) {
        resource_manage::get_instance().load_image("platform", "./res/platforms/1.png");
        // 初始化三层金字塔平台（每层各两个）
        m_platforms.emplace_back(240, 500); 
        m_platforms.emplace_back(240, 350);  
        m_platforms.emplace_back(240, 200);  
        m_platforms.emplace_back(640, 200);
        m_platforms.emplace_back(640, 350); 
        m_platforms.emplace_back(640, 500);

        // 加载平台资源（在游戏初始化时调用）
        
    }

    void draw() {  // 绘制地图与平台
        setbkcolor(RGB(0x00, 0x00, 0x00));  // 背景色
        cleardevice();
       
        for (auto& p : m_platforms) p.draw();
    }

    const std::vector<platform>& get_platforms() const { return m_platforms; }
    int get_width() const { return m_width; }
};