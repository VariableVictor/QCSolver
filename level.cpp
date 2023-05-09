// level.cpp
#include "level.h"


// 定义一个函数，用于从json文件中读取数据，并返回一个包含Slider结构体的向量和一个包含地图尺寸的数组
std::pair<std::vector<Slider>, std::array<int, 2>> read_json(const std::string& filename)
{
  std::vector<Slider> vSliders; // 定义一个空的向量，用于存储结果
  std::array<int, 2> aSize; // 定义一个大小为2的数组，用于存储地图尺寸
  json_error_t jError; // 定义一个json错误对象，用于存储错误信息

  // 假设已经从文件中解析出了一个json_t类型的值jRoot
  // 从文件中读取json数据，并返回根节点指针，如果失败则返回NULL，并将错误信息存储在jError对象中
  json_t *jRoot = json_load_file(filename.c_str(), 0, &jError);
  if (jRoot)
  { // 如果读取成功
    json_t *jMapsize = json_object_get(jRoot, "mapsize");

    if (json_is_array(jMapsize))
    { // 从jMapsize中获取第一个和第二个元素，它们应该是整数
      json_t *jWidth = json_array_get(jMapsize, 0);
      json_t *jHeight = json_array_get(jMapsize, 1);
      if (json_is_integer(jWidth) && json_is_integer(jHeight))
      { // 获取并打印宽度和高度的值
        aSize[0] = json_integer_value(jWidth);
        aSize[1] = json_integer_value(jHeight);
        std::cout << "Map size: " << aSize[0] << " x " << aSize[1] << std::endl;
      }
    }

    // 从root中获取sliders元素，它应该是一个数组
    json_t *jSliders = json_object_get(jRoot, "sliders");

    if (json_is_array(jSliders))
    { // 遍历jSliders中的每个元素，它们应该也是数组
      size_t index;
      json_t *jSlider;
      json_array_foreach(jSliders, index, jSlider)
      {
        if (json_is_array(jSlider))
        {
          // 从slider中获取四个元素，分别是布尔值、整数、整数和整数
          json_t *jHori = json_array_get(jSlider, 0);
          json_t *jLeng = json_array_get(jSlider, 1);
          json_t *jTrack = json_array_get(jSlider, 2);
          json_t *jPos = json_array_get(jSlider, 3);
          if (json_is_boolean(jHori) && json_is_integer(jLeng) && 
              json_is_integer(jTrack) && json_is_integer(jPos))
          {
            Slider sTemp; // 定义一个Slider结构体
                          // 获取并打印这四个元素的值
            sTemp.bHorizontal = json_boolean_value(jHori);
            sTemp.iLength     = json_integer_value(jLeng);
            sTemp.iTrack      = json_integer_value(jTrack);
            sTemp.iPosition   = json_integer_value(jPos);
            vSliders.push_back(sTemp);
            std::cout << "Slider " << index << ": "
              << sTemp.bHorizontal << ", " << sTemp.iLength << ", " << sTemp.iTrack << ", " << sTemp.iPosition 
              << std::endl;
          }
        }
      }
    }
  }
  else
  { // 如果读取失败
    std::cerr << "Error: cannot load file " << filename << std::endl; // 输出错误信息
    std::cerr << "Error: on line " << jError.line << ", column " << jError.column << ", " << jError.text << std::endl; // 输出错误位置和原因
  }
  return {vSliders, aSize}; // 返回结果向量和地图尺寸数组
}

// 定义一个函数，用于打印Slider结构体的内容
void print_slider(const Slider& s) {
  std::cout << "horizontal: " << std::boolalpha << s.bHorizontal << std::endl; // 打印horizontal成员变量，并将布尔值转换为true或false字符串
  std::cout << "length: " << s.iLength << std::endl; // 打印length成员变量
  std::cout << "track: " << s.iTrack << std::endl; // 打印track成员变量
  std::cout << "position: " << s.iPosition << std::endl; // 打印position成员变量
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
        if (s.bHorizontal) { // 如果当前滑块是横向的
            int row = s.iTrack; // 获取当前滑块所在的行号
            int start = s.iPosition; // 获取当前滑块的起始位置
            int end = start + s.iLength - 1; // 获取当前滑块的结束位置
            for (int j = start; j <= end; j++) { // 遍历当前滑块所占的列
                map[row][j] = c; // 将对应的格子设为当前滑块的打印符号
            }
        } else { // 如果当前滑块是纵向的
            int col = s.iTrack; // 获取当前滑块所在的列号
            int start = s.iPosition; // 获取当前滑块的起始位置
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
