#pragma once

#ifndef STRINGPROCESSOR_H
#define STRINGPROCESSOR_H

#include <Windows.h>
#include <string>

enum CutPos : char
{
	Cut_Head,
	Cut_Tail
};

enum CutMode : char
{
	Cut_Save,
	Cut_Remove
};

std::string StringWideToMultiByte(const std::wstring Wide);
std::wstring StringMultiBytetoWide(const std::string MultiByte);

std::string StringCut(const std::string String, size_t CutLen, CutPos Pos, CutMode Mode);
std::wstring StringCut(const std::wstring String, size_t CutLen, CutPos Pos, CutMode Mode);
std::string StringCut(const std::string String, char CutChar, CutPos Pos, CutMode Mode);
std::wstring StringCut(const std::wstring String, wchar_t CutChar, CutPos Pos, CutMode Mode);

bool IsStringMatchingHead(const std::string Head, const std::string FullString);
bool IsStringMatchingHead(const std::wstring Head, const std::wstring FullString);

#endif // !STRINGCONVERSION_H
