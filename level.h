
//level.h
#ifndef LEVEL_H //防止头文件被重复包含
#define LEVEL_H 

// 引入必要的头文件
#include <vector>
#include <string>
#include <array>
#include <iostream>

#include <jansson.h> // 用于处理json格式的数据，需要安装jansson库

//定义一个结构体，用来表示滑块的信息
struct Slider {
    bool bHorizontal; // 第一个元素，表示是否是横向滑块
    int  iLength; // 第二个元素，表示滑块长度
    int  iTrack; // 第三个元素，表示滑块所在滑轨（横块所在横行，纵块代表所在竖列）
    int  iPosition; // 第四个元素，表示滑块的自由活动位置
};

// 声明一个函数，用于从json文件中读取数据，并返回一个包含Slider结构体的向量和一个包含地图尺寸的数组
std::pair<std::vector<Slider>, std::array<int, 2>> read_json(const std::string& filename);

// 声明一个函数，用于打印Slider结构体的内容
void print_slider(const Slider& s);
// 声明一个函数，用于将滑块打印在地图上
void print_map(const std::vector<Slider>& sliders, const std::array<int, 2>& size); 
#endif /* ifndef LEVEL_H */
