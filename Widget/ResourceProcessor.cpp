#include "ResourceProcessor.h"


BOOL ExpResource(LPCWSTR lpPath, UINT nID, LPCWSTR lpType, HMODULE hModule)
{
	HRSRC hRsrc = FindResourceW(hModule, MAKEINTRESOURCEW(nID), lpType);
	if (hRsrc)
	{
		HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
		if (hGlobal)
		{
			LPCSTR lpData = (LPCSTR)LockResource(hGlobal);
			DWORD cbSize = SizeofResource(hModule, hRsrc);
			std::fstream File;
			File.open(lpPath, std::ios::out | std::ios::binary | std::ios::trunc);
			if (File.is_open())
			{
				File.write(lpData, cbSize);
				File.close();
				FreeResource(hGlobal);
				return TRUE;
			}
			FreeResource(hGlobal);
		}
	}
	return FALSE;
}

BOOL ExpResource(LPCSTR lpPath, UINT nID, LPCSTR lpType, HMODULE hModule)
{
	HRSRC hRsrc = FindResourceA(hModule, MAKEINTRESOURCEA(nID), lpType);
	if (hRsrc)
	{
		HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
		if (hGlobal)
		{
			LPCSTR lpData = (LPCSTR)LockResource(hGlobal);
			DWORD cbSize = SizeofResource(hModule, hRsrc);
			std::fstream File;
			File.open(lpPath, std::ios::out | std::ios::binary | std::ios::trunc);
			if (File.is_open())
			{
				File.write(lpData, cbSize);
				File.close();
				FreeResource(hGlobal);
				return TRUE;
			}
			FreeResource(hGlobal);
		}
	}
	return FALSE;
}

DWORD GetResource(DWORD cbSize, LPVOID lpBuffer, UINT nID, LPCSTR lpType, HMODULE hModule)
{
	HRSRC hRsrc = FindResourceA(hModule, MAKEINTRESOURCEA(nID), lpType);
	if (hRsrc)
	{
		HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
		if (hGlobal)
		{
			DWORD _cbSize = SizeofResource(hModule, hRsrc);
			if (cbSize >= _cbSize)
			{
				LPCSTR lpData = (LPCSTR)LockResource(hGlobal);
				memcpy(lpBuffer, lpData, _cbSize);
			}
			FreeResource(hGlobal);
			return _cbSize;
		}
	}
	return 0;
}

DWORD GetResource(DWORD cbSize, LPVOID lpBuffer, UINT nID, LPCWSTR lpType, HMODULE hModule)
{
	HRSRC hRsrc = FindResourceW(hModule, MAKEINTRESOURCEW(nID), lpType);
	if (hRsrc)
	{
		HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
		if (hGlobal)
		{
			DWORD _cbSize = SizeofResource(hModule, hRsrc);
			if (cbSize >= _cbSize)
			{
				LPCSTR lpData = (LPCSTR)LockResource(hGlobal);
				memcpy(lpBuffer, lpData, _cbSize);
			}
			FreeResource(hGlobal);
			return _cbSize;
		}
	}
	return 0;
}
