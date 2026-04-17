#ifndef KEYBOARDWINDOW_H
#define KEYBOARDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QMap>
#include <QLineEdit>

class KeyboardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardWindow(QWidget *parent = nullptr);

private slots:
    void checkKeyPress();       // 检测按键状态的槽函数
    void onResetClicked();      // 重置按钮点击事件的槽函数

private:
    void createKeyboard();      // 创建键盘界面
    void createStatusBar();     // 创建状态栏界面
    
    QMap<int, QPushButton*> m_keyMap;   // 虚拟键码到按钮的映射
    QMap<int, int> m_pressCount;        // 按键按下次数
    QMap<int, bool> m_isLongLight;      // 是否常亮状态

    QLineEdit* vkLabel;         // 显示虚拟键码的标签
    QLineEdit* scanLabel;       // 显示扫描码的标签
};

#endif // KEYBOARDWINDOW_H