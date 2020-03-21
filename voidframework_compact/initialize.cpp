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

HANDLE processHandle;
DWORD processIdentifier;
DWORD dwPanoramaClient;
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

DWORD playerBase;
//->
int localPlayerTeam;
int xhairEntity;



DWORD EntityBase;
//->
int EntityTeam;
int EntityHealth;

//To write color struct in 1 operation.
struct colors
{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;
};

//hwnd
HWND hwndCstrikeWindow = NULL;

DWORD WINAPI Triggerbot(LPVOID PARAMS) {
	while (true) {
			while (GetAsyncKeyState(0x5)) {
				ReadProcessMemory(processHandle, (LPVOID)(dwPanoramaClient + dwLocalPlayer), &playerBase, sizeof(playerBase), NULL);
				ReadProcessMemory(processHandle, (LPVOID)(playerBase + 0xF4), &localPlayerTeam, sizeof(localPlayerTeam), NULL);
				ReadProcessMemory(processHandle, (LPVOID)(playerBase + m_iCrosshairId), &xhairEntity, sizeof(xhairEntity), NULL);
				ReadProcessMemory(processHandle, (LPVOID)(dwPanoramaClient + dwEntityList + (xhairEntity - 1) * 0x10), &EntityBase, sizeof(EntityBase), NULL);
				ReadProcessMemory(processHandle, (LPVOID)(EntityBase + 0xF4), &EntityTeam, sizeof(EntityTeam), NULL);
				ReadProcessMemory(processHandle, (LPVOID)(EntityBase + m_iHealth), &EntityHealth, sizeof(EntityHealth), NULL);
				if (xhairEntity > 0) {
					if (EntityTeam != localPlayerTeam && EntityHealth > 0) {

						mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
					}
				}
				Sleep(1);
			}		
	}
	return 0;
}

DWORD WINAPI CheatEntryPoint(LPVOID PARAMS) {

		std::cout << "VoidFramework by Void-Development\n";
		std::cout << "www.github.com/voidzero-development\n";
		std::cout << "Waiting for CS:GO!\n";

		do {
			hwndCstrikeWindow = FindWindowA(0, "Counter-Strike: Global Offensive");
		} while (hwndCstrikeWindow == NULL);

		GetWindowThreadProcessId(hwndCstrikeWindow, &processIdentifier);
		processHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, processIdentifier);

		Sleep(10000);

		dwPanoramaClient = GetModuleBaseAdress((LPSTR)"client_panorama.dll", processIdentifier);
		dwEngine = GetModuleBaseAdress((LPSTR)"engine.dll", processIdentifier);

		std::cout << "Panorama Client: " << dwPanoramaClient << std::endl;
		std::cout << "Engine: " << dwEngine << std::endl;
	
		CreateThread(0, 0, &Triggerbot, 0, 0, 0);

	return TRUE;
}