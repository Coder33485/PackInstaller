#include <Shlwapi.h>

#include "FileProcessor.h"

#pragma comment(lib, "shlwapi.lib")

bool PathExist(LPCSTR Path)
{
	if (PathFileExistsA(Path))
	{
		return true;
	}
	return false;
}

bool PathExist(LPCWSTR Path)
{
	if (PathFileExistsW(Path))
	{
		return true;
	}
	return false;
}

bool GetLocalPath(LPSTR PathBuffer, DWORD BufferLength)
{
	if (GetModuleFileNameA(nullptr, PathBuffer, BufferLength) == 0)
	{
		return false;
	}
	return true;
}

bool GetLocalPath(LPWSTR PathBuffer, DWORD BufferLength)
{
	if (GetModuleFileNameW(nullptr, PathBuffer, BufferLength) == 0)
	{
		return false;
	}
	return true;
}

bool GetLocalName(LPSTR PathBuffer, DWORD BufferLength)
{
	std::string Path;
	if (!GetLocalPath(PathBuffer, BufferLength))
	{
		return false;
	}
	Path = StringCut(PathBuffer, '\\', Cut_Tail, Cut_Save);
	memset(PathBuffer, 0, BufferLength);
	strcpy_s(PathBuffer, BufferLength, Path.c_str());
	return true;
}

bool GetLocalName(LPWSTR PathBuffer, DWORD BufferLength)
{
	std::wstring Path;
	if (!GetLocalPath(PathBuffer, BufferLength))
	{
		return false;
	}
	Path = StringCut(PathBuffer, L'\\', Cut_Tail, Cut_Save);
	memset(PathBuffer, 0, BufferLength * sizeof(WCHAR));
	wcscpy_s(PathBuffer, BufferLength, Path.c_str());
	return true;
}

bool GetLocalFolderPath(LPSTR PathBuffer, DWORD BufferLength)
{
	std::string FullPath, Path;
	if (!GetLocalPath(PathBuffer, BufferLength))
	{
		return false;
	}
	FullPath = StringCut(PathBuffer, '\\', Cut_Tail, Cut_Remove);
	memset(PathBuffer, 0, BufferLength);
	strcpy_s(PathBuffer, BufferLength, FullPath.c_str());
	return true;
}

bool GetLocalFolderPath(LPWSTR PathBuffer, DWORD BufferLength)
{
	std::wstring FullPath, Path;
	if (!GetLocalPath(PathBuffer, BufferLength))
	{
		return false;
	}
	FullPath = StringCut(PathBuffer, L'\\', Cut_Tail, Cut_Remove);
	memset(PathBuffer, 0, BufferLength * sizeof(WCHAR));
	wcscpy_s(PathBuffer, BufferLength, FullPath.c_str());
	return true;
}

bool GetLocalFolderName(LPSTR PathBuffer, DWORD BufferLength)
{
	std::string FullPath, Path;
	if (!GetLocalFolderPath(PathBuffer, BufferLength))
	{
		return false;
	}
	FullPath = StringCut(PathBuffer, '\\', Cut_Tail, Cut_Save);
	memset(PathBuffer, 0, BufferLength);
	strcpy_s(PathBuffer, BufferLength, FullPath.c_str());
	return true;
}

bool GetLocalFolderName(LPWSTR PathBuffer, DWORD BufferLength)
{
	std::wstring FullPath, Path;
	if (!GetLocalFolderPath(PathBuffer, BufferLength))
	{
		return false;
	}
	FullPath = StringCut(PathBuffer, L'\\', Cut_Tail, Cut_Save);
	memset(PathBuffer, 0, BufferLength * sizeof(WCHAR));
	wcscpy_s(PathBuffer, BufferLength, FullPath.c_str());
	return true;
}

int Delete(LPCWSTR Path)
{
	std::wstring path = Path;
	path.push_back(0);
	if (!PathFileExistsW(path.c_str()))
	{
		return 0;
	}
	SHFILEOPSTRUCTW FileOp;
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
	FileOp.hNameMappings = nullptr;
	FileOp.hwnd = nullptr;
	FileOp.lpszProgressTitle = nullptr;
	FileOp.pFrom = path.c_str();
	FileOp.pTo = nullptr;
	FileOp.wFunc = FO_DELETE;
	return SHFileOperationW(&FileOp);
}

int Delete(LPCSTR Path)
{
	std::string path = Path;
	path.push_back(0);
	if (!PathFileExistsA(path.c_str()))
	{
		return 0;
	}
	SHFILEOPSTRUCTA FileOp;
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
	FileOp.hNameMappings = nullptr;
	FileOp.hwnd = nullptr;
	FileOp.lpszProgressTitle = nullptr;
	FileOp.pFrom = path.c_str();
	FileOp.pTo = nullptr;
	FileOp.wFunc = FO_DELETE;
	return SHFileOperationA(&FileOp);
}

bool CopyPath(LPCWSTR PathTo, LPCWSTR PathFrom)
{
	std::wstring pathto = PathTo, pathfrom = PathFrom;
	pathto.push_back(0);
	pathfrom.push_back(0);
	SHFILEOPSTRUCTW FileOp = { 0 };
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;
	FileOp.pFrom = pathto.c_str();
	FileOp.pTo = pathfrom.c_str();
	FileOp.wFunc = FO_COPY;
	return SHFileOperationW(&FileOp) == 0;
}

bool CopyPath(LPCSTR PathTo, LPCSTR PathFrom)
{
	std::string pathto = PathTo, pathfrom = PathFrom;
	pathto.push_back(0);
	pathfrom.push_back(0);
	SHFILEOPSTRUCTA FileOp = { 0 };
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;
	FileOp.pFrom = pathto.c_str();
	FileOp.pTo = pathfrom.c_str();
	FileOp.wFunc = FO_COPY;
	return SHFileOperationA(&FileOp) == 0;
}

bool RenameFile(LPCWSTR PathTo, LPCWSTR PathFrom)
{
	std::wstring pathto = PathTo, pathfrom = PathFrom;
	pathto.push_back(0);
	pathfrom.push_back(0);
	SHFILEOPSTRUCTW FileOp = { 0 };
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;   //不出现确认对话框 
	FileOp.pFrom = pathto.c_str();
	FileOp.pTo = pathfrom.c_str();
	FileOp.wFunc = FO_RENAME;
	return SHFileOperationW(&FileOp) == 0;
}

bool RenameFile(LPCSTR PathTo, LPCSTR PathFrom)
{
	std::string pathto = PathTo, pathfrom = PathFrom;
	pathto.push_back(0);
	pathfrom.push_back(0);
	SHFILEOPSTRUCTA FileOp = { 0 };
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;   //不出现确认对话框 
	FileOp.pFrom = pathto.c_str();
	FileOp.pTo = pathfrom.c_str();
	FileOp.wFunc = FO_RENAME;
	return SHFileOperationA(&FileOp) == 0;
}

bool SetFilePermission(LPCSTR Path, LPCSTR Account, DWORD Permission)
{
	EXPLICIT_ACCESS_A ea;
	PACL pNewDacl = nullptr;
	PACL pOldDacl = nullptr;
	LPSTR _Path = new CHAR[strlen(Path) + 2], _Account = new CHAR[strlen(Account) + 2];
	memset(_Path, 0, strlen(Path) + 2);
	memset(_Account, 0, strlen(Account) + 2);
	strcpy_s(_Path, strlen(Path) + 1, Path);
	strcpy_s(_Account, strlen(Account) + 1, Account);
	if (ERROR_SUCCESS != GetNamedSecurityInfoA(Path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, &pOldDacl, nullptr, nullptr))
	{
		delete[] _Path;
		delete[] _Account;
		return false;
	}
	BuildExplicitAccessWithNameA(&ea, _Account, Permission, GRANT_ACCESS, SUB_CONTAINERS_AND_OBJECTS_INHERIT);
	if (ERROR_SUCCESS != ::SetEntriesInAclA(1, &ea, pOldDacl, &pNewDacl))
	{
		delete[] _Path;
		delete[] _Account;
		return false;
	}
	if (ERROR_SUCCESS != ::SetNamedSecurityInfoA(_Path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, pNewDacl, nullptr))
	{
		delete[] _Path;
		delete[] _Account;
		return false;
	}
	if (nullptr != pNewDacl)
	{
		LocalFree(pNewDacl);
	}
	delete[] _Path;
	delete[] _Account;
	return true;
}

bool SetFilePermission(LPCWSTR Path, LPCWSTR Account, DWORD Permission)
{
	EXPLICIT_ACCESS_W ea;
	PACL pNewDacl = nullptr;
	PACL pOldDacl = nullptr;
	LPWSTR _Path = new WCHAR[wcslen(Path) + 2], _Account = new WCHAR[wcslen(Account) + 2];
	memset(_Path, 0, (wcslen(Path) + 2) * sizeof(WCHAR));
	memset(_Account, 0, (wcslen(Account) + 2) * sizeof(WCHAR));
	wcscpy_s(_Path, wcslen(Path) + 1, Path);
	wcscpy_s(_Account, wcslen(Account) + 1, Account);
	if (ERROR_SUCCESS != GetNamedSecurityInfoW(Path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, &pOldDacl, nullptr, nullptr))
	{
		delete[] _Path;
		delete[] _Account;
		return false;
	}
	BuildExplicitAccessWithNameW(&ea, _Account, Permission, GRANT_ACCESS, SUB_CONTAINERS_AND_OBJECTS_INHERIT);
	if (ERROR_SUCCESS != ::SetEntriesInAclW(1, &ea, pOldDacl, &pNewDacl))
	{
		delete[] _Path;
		delete[] _Account;
		return false;
	}
	if (ERROR_SUCCESS != ::SetNamedSecurityInfoW(_Path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, pNewDacl, nullptr))
	{
		delete[] _Path;
		delete[] _Account;
		return false;
	}
	if (nullptr != pNewDacl)
	{
		LocalFree(pNewDacl);
	}
	delete[] _Path;
	delete[] _Account;
	return true;
}

bool SetFilePermission(LPCSTR Path, bool Least)
{
	LPSTR _Path = new CHAR[strlen(Path) + 2];
	memset(_Path, 0, strlen(Path) + 2);
	strcpy_s(_Path, strlen(Path) + 1, Path);
	if (ERROR_SUCCESS != ::SetNamedSecurityInfoA(_Path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, nullptr, nullptr))
	{
		delete[] _Path;
		return false;
	}
	delete[] _Path;
	SetFilePermission(Path, "SYSTEM", GENERIC_ALL);
	SetFilePermission(Path, "Administrators", GENERIC_ALL);
	if (!Least)
	{
		SetFilePermission(Path, "Authenticated Users", GENERIC_READ | GENERIC_EXECUTE);
	}
	return true;
}

bool SetFilePermission(LPCWSTR Path, bool Least)
{
	LPWSTR _Path = new WCHAR[wcslen(Path) + 2];
	memset(_Path, 0, (wcslen(Path) + 2) * sizeof(WCHAR));
	wcscpy_s(_Path, wcslen(Path) + 1, Path);
	if (ERROR_SUCCESS != ::SetNamedSecurityInfoW(_Path, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, nullptr, nullptr))
	{
		delete[] _Path;
		return false;
	}
	delete[] _Path;
	SetFilePermission(Path, L"SYSTEM", GENERIC_ALL);
	SetFilePermission(Path, L"Administrators", GENERIC_ALL);
	if (!Least)
	{
		SetFilePermission(Path, L"Authenticated Users", GENERIC_READ | GENERIC_EXECUTE);
	}
	return true;
}

bool CreateShotCut(LPCWSTR FilePath, LPCWSTR ShotCutPath, LPCWSTR WorkingDir, LPCWSTR IconPath, LPCWSTR Description)
{
	CoInitialize(nullptr);
	IShellLink* pShellLink = nullptr;

	HRESULT hres;
	hres = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_ALL, IID_IShellLink, (void**)&pShellLink);

	if (SUCCEEDED(hres))
	{
		pShellLink->SetPath(FilePath);
		pShellLink->SetDescription(Description);
		pShellLink->SetIconLocation(IconPath, 0);
		pShellLink->SetWorkingDirectory(WorkingDir);

		IPersistFile* pPersistFile;
		hres = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);

		if (SUCCEEDED(hres))
		{
			hres = pPersistFile->Save(ShotCutPath, TRUE);
			pPersistFile->Release();
		}
		else
		{
			return false;
		}

		pShellLink->Release();
	}
	else
	{
		return false;
	}
	CoUninitialize();
	return true;
}