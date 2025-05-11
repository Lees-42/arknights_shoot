// src/core/math_utils.h <<< 新增基础结构体定义
#pragma once

// 二维向量结构体（独立于物理引擎，避免循环引用）
struct Vector2 {
    float x = 0;
    float y = 0;
};