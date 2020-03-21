#pragma once
#include "stdafx.h"

DWORD GetModuleBaseAdress(LPSTR lpModuleName, DWORD dwProcessId)
{
	MODULEENTRY32 lpModEntryPoint = { 0 };
	HANDLE handleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
	if (!handleSnap)	return NULL;
	lpModEntryPoint.dwSize = sizeof(lpModEntryPoint);
	BOOL bModule = Module32First(handleSnap, &lpModEntryPoint);
	while (bModule)
	{
		if (!strcmp(lpModEntryPoint.szModule, lpModuleName))
		{
			CloseHandle(handleSnap);
			return (DWORD)lpModEntryPoint.modBaseAddr;
		}
		bModule = Module32Next(handleSnap, &lpModEntryPoint);
	}
	CloseHandle(handleSnap);
	return NULL;
}
