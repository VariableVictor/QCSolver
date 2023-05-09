//1.需要将滑块数据转换为固定数据和可变数据（不同滑块的位置）
//2.重写printmap函数（是否用类封装）
//3.设计树遍历算法，探索解法

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
