#include <QApplication>
#include "keyboardwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);     // 创建应用程序对象
    KeyboardWindow w;               // 创建主窗口对象
    w.show();                       // 显示窗口
    return a.exec();                // 进入事件循环
}