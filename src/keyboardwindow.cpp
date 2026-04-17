#include "keyboardwindow.h"
#include <windows.h>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

KeyboardWindow::KeyboardWindow(QWidget *parent) : QWidget(parent)   // 构造函数
{
    setWindowTitle("键盘检测工具");
    setFixedSize(1050, 400); // 窗口大小适配布局
    setStyleSheet("background-color: #333333;"); // 背景深灰

    QVBoxLayout *totalLayout = new QVBoxLayout(this);
    totalLayout->setSpacing(10);
    totalLayout->setContentsMargins(10, 10, 10, 10);

    createKeyboard();       // 创建键盘界面

    createStatusBar();      // 创建状态栏界面

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &KeyboardWindow::checkKeyPress);
    timer->start(10);
}

void KeyboardWindow::createKeyboard()
{
    // 主布局：整体用水平布局，左边主键盘 + 右边功能区 + 数字区
    QWidget *keyWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(keyWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10,10,10,10);

    // --- 左边主键盘区 ---
    QWidget *leftWidget = new QWidget;
    QGridLayout *leftLayout = new QGridLayout(leftWidget);
    leftLayout->setSpacing(4);
    leftLayout->setContentsMargins(0,0,0,0);

    // --- 右边功能键区（Insert/Delete 等）---
    QWidget *funcWidget = new QWidget;
    QGridLayout *funcLayout = new QGridLayout(funcWidget);
    funcLayout->setSpacing(4);
    funcLayout->setContentsMargins(0,0,0,0);

    // --- 最右侧数字小键盘区 ---
    QWidget *numWidget = new QWidget;
    QGridLayout *numLayout = new QGridLayout(numWidget);
    numLayout->setSpacing(4);
    numLayout->setContentsMargins(0,0,0,0);

    // 通用按键创建函数
    auto addKey = [&](QGridLayout *layout, const QString &text, int vk, int row, int col, int w = 1, int h = 1) {
        QPushButton *btn = new QPushButton(text);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: white;
                color: black;
                border: 1px solid #aaa;
                border-radius: 3px;
            }
        )");
        btn->setFixedSize(40 * w, 40 * h);
        layout->addWidget(btn, row, col, h, w);
        m_keyMap[vk] = btn;
        m_pressCount[vk] = 0;
        m_isLongLight[vk] = false;
    };

     // =====================================
    // 1. 主键盘区（左边）
    // =====================================

    // 第0行：功能键
    addKey(leftLayout, "Esc", VK_ESCAPE, 0, 0);
    addKey(leftLayout, "F1", VK_F1, 0, 2);
    addKey(leftLayout, "F2", VK_F2, 0, 3);
    addKey(leftLayout, "F3", VK_F3, 0, 4);
    addKey(leftLayout, "F4", VK_F4, 0, 5);
    addKey(leftLayout, "F5", VK_F5, 0, 7);
    addKey(leftLayout, "F6", VK_F6, 0, 8);
    addKey(leftLayout, "F7", VK_F7, 0, 9);
    addKey(leftLayout, "F8", VK_F8, 0, 10);
    addKey(leftLayout, "F9", VK_F9, 0, 12);
    addKey(leftLayout, "F10", VK_F10, 0, 13);
    addKey(leftLayout, "F11", VK_F11, 0, 14);
    addKey(leftLayout, "F12", VK_F12, 0, 15);

    // 第1行：数字/符号键
    addKey(leftLayout, "`\n~", 0xC0, 1, 0);
    addKey(leftLayout, "1\n!", '1', 1, 1);
    addKey(leftLayout, "2\n@", '2', 1, 2);
    addKey(leftLayout, "3\n#", '3', 1, 3);
    addKey(leftLayout, "4\n$", '4', 1, 4);
    addKey(leftLayout, "5\n%", '5', 1, 5);
    addKey(leftLayout, "6\n^", '6', 1, 6);
    addKey(leftLayout, "7\n&", '7', 1, 7);
    addKey(leftLayout, "8\n*", '8', 1, 8);
    addKey(leftLayout, "9\n(", '9', 1, 9);
    addKey(leftLayout, "0\n)", '0', 1, 10);
    addKey(leftLayout, "-\n_", 0xBD, 1, 11);
    addKey(leftLayout, "=\n+", 0xBB, 1, 12);
    addKey(leftLayout, "Back\nSpace", VK_BACK, 1, 13, 3);

    // 第2行：Tab + 字母
    addKey(leftLayout, "Tab", VK_TAB, 2, 0, 2);
    addKey(leftLayout, "Q", 'Q', 2, 2);
    addKey(leftLayout, "W", 'W', 2, 3);
    addKey(leftLayout, "E", 'E', 2, 4);
    addKey(leftLayout, "R", 'R', 2, 5);
    addKey(leftLayout, "T", 'T', 2, 6);
    addKey(leftLayout, "Y", 'Y', 2, 7);
    addKey(leftLayout, "U", 'U', 2, 8);
    addKey(leftLayout, "I", 'I', 2, 9);
    addKey(leftLayout, "O", 'O', 2, 10);
    addKey(leftLayout, "P", 'P', 2, 11);
    addKey(leftLayout, "[\n{", 0xDB, 2, 12);
    addKey(leftLayout, "]\n}", 0xDD, 2, 13);
    addKey(leftLayout, "\\\n|", 0xDC, 2, 14, 2);

    // 第3行：CapsLock + 字母
    addKey(leftLayout, "Caps\nLock", VK_CAPITAL, 3, 0, 2);
    addKey(leftLayout, "A", 'A', 3, 2);
    addKey(leftLayout, "S", 'S', 3, 3);
    addKey(leftLayout, "D", 'D', 3, 4);
    addKey(leftLayout, "F", 'F', 3, 5);
    addKey(leftLayout, "G", 'G', 3, 6);
    addKey(leftLayout, "H", 'H', 3, 7);
    addKey(leftLayout, "J", 'J', 3, 8);
    addKey(leftLayout, "K", 'K', 3, 9);
    addKey(leftLayout, "L", 'L', 3, 10);
    addKey(leftLayout, ";\n:", 0xBA, 3, 11);
    addKey(leftLayout, "'\n\"", 0xDE, 3, 12);
    addKey(leftLayout, "Enter", VK_RETURN, 3, 13, 3);

    // 第4行：Shift + 字母
    addKey(leftLayout, "Shift", VK_LSHIFT, 4, 0, 3);
    addKey(leftLayout, "Z", 'Z', 4, 3);
    addKey(leftLayout, "X", 'X', 4, 4);
    addKey(leftLayout, "C", 'C', 4, 5);
    addKey(leftLayout, "V", 'V', 4, 6);
    addKey(leftLayout, "B", 'B', 4, 7);
    addKey(leftLayout, "N", 'N', 4, 8);
    addKey(leftLayout, "M", 'M', 4, 9);
    addKey(leftLayout, ",\n<", 0xBC, 4, 10);
    addKey(leftLayout, ".\n>", 0xBE, 4, 11);
    addKey(leftLayout, "/\n?", 0xBF, 4, 12);
    addKey(leftLayout, "Shift", VK_RSHIFT, 4, 13, 3);

    // 第5行：Ctrl/Win/Alt + 空格
    addKey(leftLayout, "Ctrl", VK_LCONTROL, 5, 0);
    addKey(leftLayout, "Win", VK_LWIN, 5, 1);
    addKey(leftLayout, "Alt", VK_LMENU, 5, 2);
    addKey(leftLayout, "Space", VK_SPACE, 5, 3, 9);
    addKey(leftLayout, "Alt", VK_RMENU, 5, 12);
    addKey(leftLayout, "Win", VK_RWIN, 5, 13);
    addKey(leftLayout, "Menu", VK_APPS, 5, 14);
    addKey(leftLayout, "Ctrl", VK_RCONTROL, 5, 15);

    // =====================================
    // 2. 中间功能键区（Print/Insert 等）
    // =====================================
    addKey(funcLayout, "Print\nScrn", VK_SNAPSHOT, 0, 0);
    addKey(funcLayout, "Scroll\nLock", VK_SCROLL, 0, 1);
    addKey(funcLayout, "Pause\nBreak", VK_PAUSE, 0, 2);

    addKey(funcLayout, "Insert", VK_INSERT, 1, 0);
    addKey(funcLayout, "Home", VK_HOME, 1, 1);
    addKey(funcLayout, "Page\nUp", VK_PRIOR, 1, 2);

    addKey(funcLayout, "Delete", VK_DELETE, 2, 0);
    addKey(funcLayout, "End", VK_END, 2, 1);
    addKey(funcLayout, "Page\nDown", VK_NEXT, 2, 2);

    // --- 第 3 行：强制空行占位 ---
    QWidget *spacer = new QWidget;
    spacer->setFixedHeight(40); // 高度和按键一致
    funcLayout->addWidget(spacer, 3, 0, 1, 3); // 占整行宽度

    addKey(funcLayout, "↑", VK_UP, 4, 1);
    addKey(funcLayout, "←", VK_LEFT, 5, 0);
    addKey(funcLayout, "↓", VK_DOWN, 5, 1);
    addKey(funcLayout, "→", VK_RIGHT, 5, 2);

    // =====================================
    // 3. 右侧数字小键盘区
    // =====================================
    QWidget *spacer1 = new QWidget;
    spacer1->setFixedHeight(40); // 高度和按键一致
    numLayout->addWidget(spacer1, 0, 0, 1, 3); // 占整行宽度

    addKey(numLayout, "Num\nLock", VK_NUMLOCK, 1, 0);
    addKey(numLayout, "/", VK_DIVIDE, 1, 1);
    addKey(numLayout, "*", VK_MULTIPLY, 1, 2);
    addKey(numLayout, "-", VK_SUBTRACT, 1, 3);

    addKey(numLayout, "7\nHome", VK_NUMPAD7, 2, 0);
    addKey(numLayout, "8\n↑", VK_NUMPAD8, 2, 1);
    addKey(numLayout, "9\nPgUp", VK_NUMPAD9, 2, 2);
    addKey(numLayout, "+", VK_ADD, 2, 3, 1, 2);

    addKey(numLayout, "4\n←", VK_NUMPAD4, 3, 0);
    addKey(numLayout, "5", VK_NUMPAD5, 3, 1);
    addKey(numLayout, "6\n→", VK_NUMPAD6, 3, 2);

    addKey(numLayout, "1\nEnd", VK_NUMPAD1, 4, 0);
    addKey(numLayout, "2\n↓", VK_NUMPAD2, 4, 1);
    addKey(numLayout, "3\nPgDn", VK_NUMPAD3, 4, 2);
    addKey(numLayout, "Enter", VK_SEPARATOR, 4, 3, 1, 2);

    addKey(numLayout, "0\nIns", VK_NUMPAD0, 5, 0, 2);
    addKey(numLayout, ".\nDel", VK_DECIMAL, 5, 2);

    // 把三个区域加入主布局
    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(funcWidget);
    mainLayout->addWidget(numWidget);

    // 最后把键盘加入总布局
    this->layout()->addWidget(keyWidget);
}

void KeyboardWindow::createStatusBar()
{
    // 状态栏整体容器
    QWidget *statusWidget = new QWidget;
    statusWidget->setStyleSheet("background-color: #eeeeee;");
    QHBoxLayout *statusLayout = new QHBoxLayout(statusWidget);
    statusLayout->setContentsMargins(25, 15, 25, 15);
    statusLayout->setSpacing(40);

    // ========== 左侧：VK、扫描码 垂直排列 ==========
    QWidget *leftContainer = new QWidget;
    QVBoxLayout *leftVLayout = new QVBoxLayout(leftContainer);
    leftVLayout->setSpacing(12);
    leftVLayout->setContentsMargins(0,0,0,0);

    // VK 标签 + 显示
    QLabel *vkTextLabel = new QLabel("VK Code:");
    vkLabel = new QLineEdit("00h (0)");
    vkLabel->setReadOnly(true);
    vkLabel->setFixedWidth(120);
    // 水平组合 VK 行
    QHBoxLayout *vkRow = new QHBoxLayout();
    vkRow->addWidget(vkTextLabel);
    vkRow->addWidget(vkLabel);
    vkRow->addStretch();

    // Scan 标签 + 显示
    QLabel *scanTextLabel = new QLabel("Scan Code:");
    scanLabel = new QLineEdit("00h (0)");
    scanLabel->setReadOnly(true);
    scanLabel->setFixedWidth(120);
    // 水平组合 Scan 行
    QHBoxLayout *scanRow = new QHBoxLayout();
    scanRow->addWidget(scanTextLabel);
    scanRow->addWidget(scanLabel);
    scanRow->addStretch();

    // 两行垂直叠放
    leftVLayout->addLayout(vkRow);
    leftVLayout->addLayout(scanRow);

    // ========== 右侧：Reset、About 按钮 ==========
    QWidget *rightContainer = new QWidget;
    QHBoxLayout *rightHLayout = new QHBoxLayout(rightContainer);
    rightHLayout->setSpacing(15);
    rightHLayout->setContentsMargins(0,0,0,0);

    QPushButton *resetBtn = new QPushButton("Reset");
    QPushButton *aboutBtn = new QPushButton("About");
    resetBtn->setFixedSize(80, 30);
    aboutBtn->setFixedSize(80, 30);

    // 按钮样式
    QString btnStyle = R"(
        QPushButton {
            background-color: #cccccc;
            border: none;
            border-radius: 4px;
            padding: 8px 20px;
            font-size: 14px;
        }
        QPushButton:pressed {
            background-color: #aaaaaa;
        }
    )";
    resetBtn->setStyleSheet(btnStyle);
    aboutBtn->setStyleSheet(btnStyle);

    // 绑定重置按钮点击事件
    connect(resetBtn, &QPushButton::clicked, this, &KeyboardWindow::onResetClicked);

    rightHLayout->addWidget(resetBtn);
    rightHLayout->addWidget(aboutBtn);


    // ========== 组装整体状态栏 ==========
    statusLayout->addWidget(leftContainer);
    statusLayout->addStretch(); // 左右两端对齐
    statusLayout->addWidget(rightContainer);


    // 把状态栏加入窗口总布局
    this->layout()->addWidget(statusWidget);
}

void KeyboardWindow::checkKeyPress()
{
    // 静态变量，只创建一次，记录按键是否处于按下状态
    static QMap<int, bool> keyDown;

    for (int vk = 8; vk < 256; ++vk) {
        if (!m_keyMap.contains(vk)) continue;

        auto btn = m_keyMap[vk];
        bool pressed = (GetAsyncKeyState(vk) & 0x8000);

        if (pressed) {
            if (!m_isLongLight[vk]) {
                // 仅在 刚按下 的那一刻计数 +1
                if (!keyDown[vk]) {
                    m_pressCount[vk]++;
                    keyDown[vk] = true;
                }
                // 按下显示：绿色 + 黑字
                btn->setStyleSheet("background-color: #f6ff00; color: black;");
            } else {
                // 已满4次：永久保持绿色+黑字
                btn->setStyleSheet("background-color: #00FF00; color: black;");
            }

            // 更新显示格式：十六进制(十进制)
            QString vkHex = QString("%1").arg(vk, 2, 16, QChar('0')).toUpper();
            vkLabel->setText(QString("%1h (%2)").arg(vkHex).arg(vk));

            UINT scanCode = MapVirtualKeyA(vk, 0);
            QString scanHex = QString("%1").arg(scanCode, 2, 16, QChar('0')).toUpper();
            scanLabel->setText(QString("%1h (%2)").arg(scanHex).arg(scanCode));
        }
        else {
            // 松开时重置状态
            keyDown[vk] = false;

            if (!m_isLongLight[vk]) {
                // 没满4次 → 恢复白色
                btn->setStyleSheet("background-color: white; color: black;");
            } else {
                // 满4次 → 保持绿色
                btn->setStyleSheet("background-color: #00FF00; color: black;");
            }
        }

        if (m_pressCount[vk] >= 4) {
            m_isLongLight[vk] = true;
        }
    }
}

void KeyboardWindow::onResetClicked()
{
    // 清空按键状态
    for(int vk : m_keyMap.keys())
    {
        m_pressCount[vk] = 0;
        m_isLongLight[vk] = false;
        m_keyMap[vk]->setStyleSheet("background-color:white; color:black;");
    }
    // 重置状态栏显示
    vkLabel->setText("00h (0)");
    scanLabel->setText("00h (0)");
}
