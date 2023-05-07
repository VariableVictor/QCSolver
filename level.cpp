// level.cpp
#include "level.h"
//#include <fstream>


// 定义一个函数，用于从json文件中读取数据，并返回一个包含Slider结构体的向量和一个包含地图尺寸的数组
std::pair<std::vector<Slider>, std::array<int, 2>> read_json(const std::string& filename)
{
  std::vector<Slider> result; // 定义一个空的向量，用于存储结果
  std::array<int, 2> size; // 定义一个大小为2的数组，用于存储地图尺寸
  json_t *root; // 定义一个json对象指针，用于存储json数据的根节点
  json_error_t error; // 定义一个json错误对象，用于存储错误信息
  root = json_load_file(filename.c_str(), 0, &error); // 从文件中读取json数据，并返回根节点指针，如果失败则返回NULL，并将错误信息存储在error对象中
  if (root)
  { // 如果读取成功
    size_t index; // 定义一个索引变量，用于遍历json数组中的每个元素
    json_t *array; // 定义一个json对象指针，用于存储json数组中的每个子数组
    json_array_foreach(root, index, array)
    { // 遍历根节点中的每个子数组
      if (index == 0)
      { // 如果是第一个子数组，则表示地图尺寸
        size[0] = json_integer_value(json_array_get(array, 0)); // 将第一个元素转换为整数，并赋值给size数组的第一个元素，表示地图宽度
        size[1] = json_integer_value(json_array_get(array, 1)); // 将第二个元素转换为整数，并赋值给size数组的第二个元素，表示地图高度
      }
      else
      { // 如果不是第一个子数组，则表示滑块信息
        Slider s; // 定义一个Slider结构体
        s.is_horizontal = json_boolean_value(json_array_get(array, 0)); // 从子数组中读取第一个元素，并转换为布尔值，并赋值给结构体的horizontal成员变量
        s.iLength = json_integer_value(json_array_get(array, 1)); // 从子数组中读取第二个元素，并转换为整数，并赋值给结构体的length成员变量
        s.iTrack = json_integer_value(json_array_get(array, 2)); // 从子数组中读取第三个元素，并转换为整数，并赋值给结构体的track成员变量
        s.iCol = json_integer_value(json_array_get(array, 3)); // 从子数组中读取第四个元素，并转换为整数，并赋值给结构体的position成员变量
        result.push_back(s); // 将结构体添加到结果向量中
      }
    }
    json_decref(root); // 减少根节点指针的引用计数，如果为0则释放内存空间
  }
  else
  { // 如果读取失败
    std::cerr << "Error: cannot load file " << filename << std::endl; // 输出错误信息
    std::cerr << "Error: on line " << error.line << ", column " << error.column << ", " << error.text << std::endl; // 输出错误位置和原因
  }
  return {result, size}; // 返回结果向量和地图尺寸数组
}

// 定义一个函数，用于打印Slider结构体的内容
void print_slider(const Slider& s) {
  std::cout << "horizontal: " << std::boolalpha << s.is_horizontal << std::endl; // 打印horizontal成员变量，并将布尔值转换为true或false字符串
  std::cout << "length: " << s.iLength << std::endl; // 打印length成员变量
  std::cout << "track: " << s.iTrack << std::endl; // 打印track成员变量
  std::cout << "position: " << s.iCol << std::endl; // 打印position成员变量
}

// 定义一个函数，用于将滑块打印在地图上
void print_map(const std::vector<Slider>& sliders, const std::array<int, 2>& size) {
    int width = size[0]; // 获取地图的宽度
    int height = size[1]; // 获取地图的高度
    char map[height][width]; // 定义一个二维字符数组，用于存储地图上的每个格子
    for (int i = 0; i < height; i++) { // 遍历每一行
        for (int j = 0; j < width; j++) { // 遍历每一列
            map[i][j] = '.'; // 将每个格子初始化为'.'，表示空白
        }
    }
    for (size_t k = 0; k < sliders.size(); k++) { // 遍历每个滑块
        Slider s = sliders[k]; // 获取当前滑块
        char c; // 定义一个字符变量，用于存储当前滑块的打印符号
        if (k == 0) { // 如果是第一个滑块
            c = '*'; // 将打印符号设为'*'
        } else { // 如果不是第一个滑块
            c = '0' + k - 1; // 将打印符号设为n-1的字符，例如'1', '2', '3'等
        }
        if (s.is_horizontal) { // 如果当前滑块是横向的
            int row = s.iTrack; // 获取当前滑块所在的行号
            int start = s.iCol; // 获取当前滑块的起始位置
            int end = start + s.iLength - 1; // 获取当前滑块的结束位置
            for (int j = start; j <= end; j++) { // 遍历当前滑块所占的列
                map[row][j] = c; // 将对应的格子设为当前滑块的打印符号
            }
        } else { // 如果当前滑块是纵向的
            int col = s.iTrack; // 获取当前滑块所在的列号
            int start = s.iCol; // 获取当前滑块的起始位置
            int end = start + s.iLength - 1; // 获取当前滑块的结束位置
            for (int i = start; i <= end; i++) { // 遍历当前滑块所占的行
                map[i][col] = c; // 将对应的格子设为当前滑块的打印符号
            }
        }
    }
    for (int i = 0; i < height; i++) { // 遍历每一行
        for (int j = 0; j < width; j++) { // 遍历每一列
            std::cout << map[i][j] << " "; // 打印每个格子，并用空格分隔
        }
        std::cout << std::endl; // 换行
    }
}
