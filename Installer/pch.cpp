// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

WCHAR
_DefaultPath[] = L"C:\\Program Files\\Installer Test Package",
_DefaultName[] = L"测试安装包",
_ExecutableFileRelativePath[] = L"Main.exe",
_HelpLink[] = L"https://www.bilibili.com",
_Publisher[] = L"Coder33485",
_RegKeyName[] = L"Installer Test Package";

CString Path;
HANDLE hProcess;
LPCWSTR
DefaultPath = _DefaultPath,
DefaultName = _DefaultName,
ExecutableFileRelativePath = _ExecutableFileRelativePath,
HelpLink = _HelpLink,
Publisher = _Publisher,
RegKeyName = _RegKeyName;