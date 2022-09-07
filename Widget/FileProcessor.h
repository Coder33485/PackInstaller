#pragma once

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <Windows.h>
#include <AccCtrl.h>
#include <AclAPI.h>
#include <ShlObj.h>
#include <string>

#include "StringProcessor.h"

bool PathExist(LPCSTR Path);
bool PathExist(LPCSTR Path);
bool GetLocalPath(LPSTR PathBuffer, DWORD BufferLength);
bool GetLocalPath(LPWSTR PathBuffer, DWORD BufferLength);
bool GetLocalName(LPSTR PathBuffer, DWORD BufferLength);
bool GetLocalName(LPWSTR PathBuffer, DWORD BufferLength);
bool GetLocalFolderPath(LPSTR PathBuffer, DWORD BufferLength);
bool GetLocalFolderPath(LPWSTR PathBuffer, DWORD BufferLength);
bool GetLocalFolderName(LPSTR PathBuffer, DWORD BufferLength);
bool GetLocalFolderName(LPWSTR PathBuffer, DWORD BufferLength);

int Delete(LPCSTR Path);
int Delete(LPCWSTR Path);
bool CopyPath(LPCSTR PathTo, LPCSTR PathFrom);
bool CopyPath(LPCWSTR PathTo, LPCWSTR PathFrom);
bool RenameFile(LPCSTR PathTo, LPCSTR PathFrom);
bool RenameFile(LPCWSTR PathTo, LPCWSTR PathFrom);
bool SetFilePermission(LPCSTR Path, LPCSTR Account, DWORD Permission = GENERIC_ALL);
bool SetFilePermission(LPCWSTR Path, LPCWSTR Account, DWORD Permission = GENERIC_ALL);
bool SetFilePermission(LPCSTR Path, bool Least = false);
bool SetFilePermission(LPCWSTR Path, bool Least = false);

bool CreateShotCut(LPCWSTR FilePath, LPCWSTR ShotCutPath, LPCWSTR WorkingDir, LPCWSTR IconPath, LPCWSTR Description);

#endif // !FILEPROCESSOR_H
