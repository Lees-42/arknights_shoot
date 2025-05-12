// resource_manage.h
#pragma once
#include <easyx.h>
#include <unordered_map>
#include <string>

class resource_manage {
private:
    std::unordered_map<std::string, IMAGE> m_images;  // ͼƬ��Դ����
    resource_manage() = default;                     // ����ģʽ
    ~resource_manage();

public:
    static resource_manage& get_instance();
    bool load_image(const std::string& key, const char* path);  // ����ͼƬ������
    bool load_image_sequence(const std::string& base_key, const char* base_path, int frame_count); // ��������֡ͼƬ
    IMAGE* get_image(const std::string& key);                   // ��ȡͼƬָ��
    void clear();                                               // �ͷ�������Դ
};

