#include <iostream>
#include <jansson.h>
#include <vector>

int main()
{
    // 假设已经从文件中解析出了一个json_t类型的值root
    json_t *jRoot = json_load_file("test1.json", 0, NULL);

    // 从root中获取mapsize元素，它应该是一个数组
    json_t *mapsize = json_object_get(jRoot, "mapsize");
    if (json_is_array(mapsize)) {
        // 从mapsize中获取第一个和第二个元素，它们应该是整数
        json_t *jWidth = json_array_get(mapsize, 0);
        json_t *jHeight = json_array_get(mapsize, 1);
        if (json_is_integer(jWidth) && json_is_integer(jHeight)) {
            // 获取并打印宽度和高度的值
            int w = json_integer_value(jWidth);
            int h = json_integer_value(jHeight);
            std::cout << "Map size: " << w << " x " << h << std::endl;
        }
    }

    // 从root中获取sliders元素，它应该是一个数组
    json_t *jSliders = json_object_get(jRoot, "sliders");
    if (json_is_array(jSliders)) {
        // 遍历sliders中的每个元素，它们应该也是数组
        size_t index;
        json_t *jSlider;
        json_array_foreach(jSliders, index, jSlider) {
            if (json_is_array(jSlider)) {
                // 从slider中获取四个元素，分别是布尔值、整数、整数和整数
                json_t *jHori = json_array_get(jSlider, 0);
                json_t *jLeng = json_array_get(jSlider, 1);
                json_t *jTrack = json_array_get(jSlider, 2);
                json_t *jPos = json_array_get(jSlider, 3);
                if (json_is_boolean(jHori) && json_is_integer(jLeng) && 
                    json_is_integer(jTrack) && json_is_integer(jPos)) {
                    // 获取并打印这四个元素的值
                    bool bHori = json_boolean_value(jHori);
                    int iLength = json_integer_value(jLeng);
                    int iTrack = json_integer_value(jTrack);
                    int iPosition = json_integer_value(jPos);
                    std::cout << "Slider " << index << ": "
                              << bHori << ", " << iLength << ", " << iTrack << ", " << iPosition 
                              << std::endl;
                }
            }
        }
    }

    // 释放root
    json_decref(jRoot);
    return 0;
}
//int main(int argc, char *argv[])
//{
//  json_t *pRoot;
//  pRoot = json_load_file("./test.json", JSON_DECODE_ANY, NULL);
//  if (0 == json_is_array(pRoot))
//  {
//    printf("file is not array");
//    return 1;
//  }
//  int iSize = json_array_size(pRoot);
//  printf("file is a array with %d elements.\n", iSize);
//
//  json_t *pSize = json_array_get(pRoot, 0);//获得地图尺寸
//  if (NULL == pSize)
//  {
//    printf("Can't get the size of map");
//    return 1;
//  }
//  if (0 == json_is_array(pSize))
//  {
//    printf("size is not a array");
//    return 1;
//  }
//  json_int_t jiSizey, jiSizex;
//
//  jiSizey = json_integer_value(json_array_get(pSize,0));
//  jiSizex = json_integer_value(json_array_get(pSize,1));
//  printf("It's a %" JSON_INTEGER_FORMAT " x %" JSON_INTEGER_FORMAT " size map\n", jiSizey, jiSizex);
//
//  for (int i = 1; i < iSize; i++)
//  {
//    json_t *pRC = json_array_get(pRoot, i);
//    bool bH = (json_true() == json_array_get(pRC, 0));
//    int irc = json_integer_value(json_array_get(pRC, 1));
//    int iy = json_integer_value(json_array_get(pRC, 2));
//    int ix = json_integer_value(json_array_get(pRC, 3));
//    if (bH)
//    {
//      printf("this RC is a Horizon RC\n");
//    }
//    else
//    {
//      printf("this RC is not a Horizon RC\n");
//    }
//    printf("%d,%d,%d\n",irc,iy,ix);
//  }
//}
