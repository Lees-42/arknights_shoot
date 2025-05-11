// resource_manage.cpp
#include "resource_manage.h"
#include <cassert>
#include <Windows.h>  // 用于 MultiByteToWideChar


resource_manage& resource_manage::get_instance() {
    static resource_manage instance;
    return instance;
}

bool resource_manage::load_image(const std::string& key, const char* path) {
    if (m_images.find(key) != m_images.end()) {  // 已加载过，直接返回成功
        return true;
    }

    IMAGE img;
    
    loadimage(&img,path);              // 使用窄字符路径加载图片

   
    if (img.getwidth() <= 0 || img.getheight() <= 0) {
        OutputDebugStringA("Invalid image size: ");
        OutputDebugStringA(path);
        return false;
    }

    m_images[key] = img;
    return true;
}

IMAGE* resource_manage::get_image(const std::string& key) {
    auto it = m_images.find(key);
    return (it != m_images.end()) ? &it->second : nullptr;
}

resource_manage::~resource_manage() { clear(); }
void resource_manage::clear() { m_images.clear(); }