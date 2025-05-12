// resource_manage.h
#pragma once
#include <easyx.h>
#include <unordered_map>
#include <string>

class resource_manage {
private:
    std::unordered_map<std::string, IMAGE> m_images;  // 图片资源缓存
    resource_manage() = default;                     // 单例模式
    ~resource_manage();

public:
    static resource_manage& get_instance();
    bool load_image(const std::string& key, const char* path);  // 加载图片到缓存
    bool load_image_sequence(const std::string& base_key, const char* base_path, int frame_count); // 加载序列帧图片
    IMAGE* get_image(const std::string& key);                   // 获取图片指针
    void clear();                                               // 释放所有资源
};

