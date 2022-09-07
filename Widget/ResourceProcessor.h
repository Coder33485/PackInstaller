#pragma once

#ifndef RESOURCEPROCESSOR_H
#define RESOURCEPROCESSOR_H

#include <Windows.h>
#include <fstream>

BOOL ExpResource(LPCSTR lpPath, UINT nID, LPCSTR lpType, HMODULE hModule = nullptr);
BOOL ExpResource(LPCWSTR lpPath, UINT nID, LPCWSTR lpType, HMODULE hModule = nullptr);

DWORD GetResource(DWORD cbSize, LPVOID lpBuffer, UINT nID, LPCSTR lpType, HMODULE hModule = nullptr);
DWORD GetResource(DWORD cbSize, LPVOID lpBuffer, UINT nID, LPCWSTR lpType, HMODULE hModule = nullptr);

#endif // !RESOURCEPROCESSOR_H
