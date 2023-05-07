// QCSolver.h
// 头文件保护
#ifndef QCSOLVER_H
#define QCSOLVER_H

// 引入必要的头文件
#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include "level.h"

// 定义程序名和版本信息的常量
const std::string PROGRAM_NAME = "QCSolver";
const std::string VERSION = "0.1";

// 声明参数处理函数
void handle_help_option();
void handle_version_option();
void handle_input_option(const std::string& filename);

#endif // QCSOLVER_H
