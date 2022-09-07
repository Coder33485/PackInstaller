#include "StringProcessor.h"

std::string StringWideToMultiByte(const std::wstring Wide)
{
	int Length = WideCharToMultiByte(CP_UTF8, 0, Wide.c_str(), Wide.size(), nullptr, 0, nullptr, nullptr);
	char* Buffer = new char[Length + 1];
	memset(Buffer, '\0', sizeof(char) * (Length + 1));
	WideCharToMultiByte(CP_UTF8, 0, Wide.c_str(), Wide.size(), Buffer, Length, nullptr, nullptr);
	std::string MultiByte(Buffer);
	delete[] Buffer;
	return MultiByte;
}

std::wstring StringMultiBytetoWide(const std::string MultiByte)
{
	DWORD Length = MultiByteToWideChar(CP_UTF8, 0, MultiByte.c_str(), -1, nullptr, 0);
	wchar_t* Buffer = new wchar_t[Length + 1];
	memset(Buffer, '\0', sizeof(wchar_t) * (Length + 1));
	MultiByteToWideChar(CP_UTF8, 0, MultiByte.c_str(), -1, Buffer, Length);
	std::wstring Wide(Buffer);
	delete[] Buffer;
	return Wide;;
}

std::string StringCut(const std::string String, size_t CutLen, CutPos Pos, CutMode Mode)
{
	std::string Buffer1, Buffer2, Null;
	if (Pos == Cut_Head)
	{
		for (size_t i = 0; i < String.length(); i++)
		{
			if (i < CutLen)
			{
				Buffer1.push_back(String[i]);
			}
			else
			{
				Buffer2.push_back(String[i]);
			}
		}
	}
	else if (Pos == Cut_Tail)
	{
		for (size_t i = String.length() - CutLen; i < String.length(); i++)
		{
			Buffer1.push_back(String[i]);
		}
		for (size_t i = 0; i < String.length() - CutLen; i++)
		{
			Buffer2.push_back(String[i]);
		}
	}
	if (Mode == Cut_Save)
	{
		return Buffer1;
	}
	else if (Mode == Cut_Remove)
	{
		return Buffer2;
	}
	return Null;
}

std::wstring StringCut(const std::wstring String, size_t CutLen, CutPos Pos, CutMode Mode)
{
	std::wstring Buffer1, Buffer2, Null;
	if (Pos == Cut_Head)
	{
		for (size_t i = 0; i < String.length(); i++)
		{
			if (i < CutLen)
			{
				Buffer1.push_back(String[i]);
			}
			else
			{
				Buffer2.push_back(String[i]);
			}
		}
	}
	else if (Pos == Cut_Tail)
	{
		for (size_t i = String.length() - CutLen; i < String.length(); i++)
		{
			Buffer1.push_back(String[i]);
		}
		for (size_t i = 0; i < String.length() - CutLen; i++)
		{
			Buffer2.push_back(String[i]);
		}
	}
	if (Mode == Cut_Save)
	{
		return Buffer1;
	}
	else if (Mode == Cut_Remove)
	{
		return Buffer2;
	}
	return Null;
}

std::string StringCut(const std::string String, char CutChar, CutPos Pos, CutMode Mode)
{
	std::string Buffer1, Buffer2, Null;
	bool Cut = false;
	size_t j = 0;
	if (Pos == Cut_Head)
	{
		for (size_t i = 0; i < String.length(); i++)
		{
			if (String[i] == CutChar)
			{
				Cut = true;
				continue;
			}
			if (!Cut)
			{
				Buffer1.push_back(String[i]);
			}
			else
			{
				Buffer2.push_back(String[i]);
			}
		}
	}
	else if (Pos == Cut_Tail)
	{
		for (size_t i = String.length(); i != -1; i--)
		{ 
			if (String[i] == CutChar)
			{
				j = i;
				break;
			}
		}
		for (size_t i = j + 1; i < String.length(); i++)
		{
			Buffer1.push_back(String[i]);
		}
		for (size_t i = 0; i < j; i++)
		{
			Buffer2.push_back(String[i]);
		}
	}
	if (Mode == Cut_Save)
	{
		return Buffer1;
	}
	else if (Mode == Cut_Remove)
	{
		return Buffer2;
	}
	return Null;
}

std::wstring StringCut(const std::wstring String, wchar_t CutChar, CutPos Pos, CutMode Mode)
{
	std::wstring Buffer1, Buffer2, Null;
	bool Cut = false;
	size_t j = 0;
	if (Pos == Cut_Head)
	{
		for (size_t i = 0; i < String.length(); i++)
		{
			if (String[i] == CutChar)
			{
				Cut = true;
				continue;
			}
			if (!Cut)
			{
				Buffer1.push_back(String[i]);
			}
			else
			{
				Buffer2.push_back(String[i]);
			}
		}
	}
	else if (Pos == Cut_Tail)
	{
		for (size_t i = String.length(); i != -1; i--)
		{ 
			if (String[i] == CutChar)
			{
				j = i;
				break;
			}
		}
		for (size_t i = j + 1; i < String.length(); i++)
		{
			Buffer1.push_back(String[i]);
		}
		for (size_t i = 0; i < j; i++)
		{
			Buffer2.push_back(String[i]);
		}
	}
	if (Mode == Cut_Save)
	{
		return Buffer1;
	}
	else if (Mode == Cut_Remove)
	{
		return Buffer2;
	}
	return Null;
}

bool IsStringMatchingHead(const std::string Head, const std::string FullString)
{
	if (Head.length() > FullString.length())
	{
		return false;
	}
	for (size_t i = 0; i < Head.length(); i++)
	{
		if (Head[i] != FullString[i])
		{
			return false;
		}
	}
	return true;
}

bool IsStringMatchingHead(const std::wstring Head, const std::wstring FullString)
{
	if (Head.length() > FullString.length())
	{
		return false;
	}
	for (size_t i = 0; i < Head.length(); i++)
	{
		if (Head[i] != FullString[i])
		{
			return false;
		}
	}
	return true;
}
