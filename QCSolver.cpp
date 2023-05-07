#include "QCSolver.h"

void handle_help_option()
{
  // 打印程序的用法，选项和版本
  std::cout << "Usage: " << PROGRAM_NAME << " [options] [input_file]\n";
  std::cout << "Options:\n";
  std::cout << "  -h, --help      Display this help message and exit\n";
  std::cout << "  -v, --version   Display the program version and exit\n";
  std::cout << "  -i, --input     Specify the input file name (default: stdin)\n";
}

void handle_version_option()
{
  // 打印程序的名称和版本
  std::cout << PROGRAM_NAME << " version " << VERSION << std::endl;
  // 退出程序
  exit(0);
}

void handle_input_option(const std::string& filename)
{
  std::pair<std::vector<Slider>, std::array<int, 2>> level = read_json(filename); // 调用read_json函数，从level.json文件中读取数据，并存储在data变量中
  std::vector<Slider> sliders = level.first; // 获取滑块向量
  std::array<int, 2> size = level.second; // 获取地图尺寸数组
  print_map(sliders, size); // 调用print_map函数，将滑块打印在地图上
}

int main(int argc, char* argv[])
{
    // 定义长选项结构体数组
    struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"input", required_argument, NULL, 'i'},
        {NULL, 0, NULL, 0}
    };

    // 定义短选项字符串
    const char* short_options = "hvi:";

    // 定义变量存储选项字符和长选项索引
    int opt;
    int option_index;

    // 使用getopt_long函数遍历所有选项
    while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
    {
        // 判断选项类型
        switch (opt)
        {
          case 'h': // 处理帮助选项
            handle_help_option();
            break;
          case 'v': // 处理版本选项
            handle_version_option();
            break;
          case 'i': // 处理输入选项
            handle_input_option(optarg);
            break;
          case '?':
            // 处理未知选项
            std::cout << "Unknown option: " << optopt << std::endl;
            exit(1);
          default: // 处理无效选项
            std::cerr << "Invalid option: " << opt << std::endl;
            exit(1);
        }
    }

    return 0;
}
