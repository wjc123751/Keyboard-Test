; 键盘检测工具 安装包脚本
#define MyAppName "键盘检测工具"
#define MyAppVersion "1.0"
#define MyExeName "KeyboardTester.exe"

[Setup]
AppName={#MyAppName}
AppVersion={#MyAppVersion}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename=键盘检测工具_安装程序
Compression=lzma2
SolidCompression=yes
PrivilegesRequired=admin
UninstallDisplayIcon={app}\{#MyExeName}

[Files]
Source: "C:\Users\16009\Desktop\KeyboardTest\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs ignoreversion

[Icons]
; 创建桌面快捷方式
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyExeName}"
; 创建开始菜单快捷方式
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyExeName}"
; 添加卸载入口
Name: "{group}\卸载 {#MyAppName}"; Filename: "{uninstallexe}"

