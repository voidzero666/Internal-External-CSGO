/**
 * Created by Voidzero-Development
 * Date: 21-03-2020
 * Time: 21:48
 * Do not redistribute without providing the source code.
 * Do not redistribute without giving credit to the creator: https://github.com/voidzero-development
 * Do not use code in commerical application.
 */
#include "stdafx.h"


//Using hazedumper, thanks alot to frk1
//https://github.com/frk1/hazedumper
#include "hazedumper.hpp"
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

HANDLE procHandle;
DWORD procId;
DWORD dwClient;
DWORD dwEngine;
int iClientState;

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

int GLent;
int GLcent;
int GLcpg;
DWORD GLPOINTR;
DWORD PlayerBase;
int hp;
int m_flags;
int teamnum;
int GLteamnum;
bool GLdormant;


bool t = true;
bool f = false;

int entCID;
DWORD entityp;
int entteamnum;
int enthp;

DWORD WINAPI Triggerbot(LPVOID PARAMS) {
	while (true) {
		
			while (GetAsyncKeyState(0x5)) {
				ReadProcessMemory(procHandle, (LPVOID)(dwClient + dwLocalPlayer), &PlayerBase, sizeof(PlayerBase), NULL);
				ReadProcessMemory(procHandle, (LPVOID)(PlayerBase + 0xF4), &teamnum, sizeof(teamnum), NULL);
				ReadProcessMemory(procHandle, (LPVOID)(PlayerBase + m_iCrosshairId), &entCID, sizeof(entCID), NULL);
				ReadProcessMemory(procHandle, (LPVOID)(dwClient + dwEntityList + (entCID - 1) * 0x10), &entityp, sizeof(entityp), NULL);
				ReadProcessMemory(procHandle, (LPVOID)(entityp + 0xF4), &entteamnum, sizeof(entteamnum), NULL);
				ReadProcessMemory(procHandle, (LPVOID)(entityp + m_iHealth), &enthp, sizeof(enthp), NULL);
				if (entCID > 0) {
					if (entteamnum != teamnum && enthp > 0) {

						mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
					}
				}
				Sleep(1);
			}		
	}
	return 0;
}


//To write color struct in 1 operation.
struct colors
{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;
};


DWORD WINAPI entry(LPVOID PARAMS) {

		std::cout << "VoidFramework by Void-Development\n";
		std::cout << "www.github.com/voidzero-development\n";

		std::cout << "Waiting for CS:GO!\n";

		HWND windowHandle = NULL;

		do {
			windowHandle = FindWindowA(0, "Counter-Strike: Global Offensive");
		} while (windowHandle == NULL);

		GetWindowThreadProcessId(windowHandle, &procId);
		procHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

		Sleep(10000);

		dwClient = GetModuleBaseAdress((LPSTR)"client_panorama.dll", procId);
		dwEngine = GetModuleBaseAdress((LPSTR)"engine.dll", procId);

		std::cout << "Panorama Client: " << dwClient << std::endl;
		std::cout << "Engine: " << dwEngine << std::endl;
	
		CreateThread(0, 0, &Triggerbot, 0, 0, 0);

	return TRUE;
}