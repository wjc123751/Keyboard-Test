# 键盘检测工具 - 打包发布说明

## 一、打包前准备
1. 确保已编译 **Release 版本**。
2. 确保已在 `CMakeLists.txt` 中添加无控制台窗口配置：
   ```cmake
   if(WIN32)
       target_link_options(KeyboardTester PRIVATE -mwindows)
   endif()
   ```
3. 进入 `build` 目录，只保留以下运行必需文件：
   - `KeyboardTester.exe`
   - 运行所需的 `.dll` 文件
   - Qt 插件文件夹（`platforms`、`styles`、`imageformats` 等）

## 二、一键打包
1. 打开 **Qt MinGW 命令提示符**，先进入项目 `build` 文件夹路径，再执行：
   ```bash
   windeployqt KeyboardTester.exe
   ```
2. 生成安装包：
   打开 Inno Setup，加载脚本文件：`KeyboardTest.iss`，按 `F7` 编译即可。

## 三、输出文件
编译成功后，会在脚本目录生成：`键盘检测工具_安装程序.exe`
**以管理员权限运行该 exe 文件**