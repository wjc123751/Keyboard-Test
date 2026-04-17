#ifndef KEYBOARDWINDOW_H
#define KEYBOARDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QMap>

class KeyboardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardWindow(QWidget *parent = nullptr);

private slots:
    void checkKeyPress();       // 检测按键状态的槽函数

private:
    void createKeyboard();      // 创建键盘界面
    
    QMap<int, QPushButton*> m_keyMap;   // 虚拟键码到按钮的映射
    QMap<int, int> m_pressCount;        // 按键按下次数
    QMap<int, bool> m_isLongLight;      // 是否常亮状态
};

#endif // KEYBOARDWINDOW_H