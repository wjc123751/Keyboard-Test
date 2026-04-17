cmake_minimum_required(VERSION 3.16)

project(KeyboardTester)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启 Qt 自动编译支持
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 强制指定 Qt 路径（你的 Qt 安装路径）
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")

# 查找 Qt 核心模块
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 添加项目源文件（按你的目录结构写全路径）
add_executable(KeyboardTester
    src/main.cpp
    src/keyboardwindow.cpp
    include/keyboardwindow.h
)

# 让 CMake 知道头文件在 include 目录里
target_include_directories(KeyboardTester PRIVATE include)

# 链接 Qt 库
target_link_libraries(KeyboardTester PRIVATE Qt6::Core Qt6::Widgets)