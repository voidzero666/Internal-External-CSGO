#include "stdafx.h"
#include "initialize.h"
/**
 * Created by Voidzero-Development
 * Date: 21-03-2020
 * Time: 21:48
 * Do not redistribute without providing the source code.
 * Do not redistribute without giving credit to the creator: https://github.com/voidzero-development
 * Do not use code in commerical application.
 */

BOOL APIENTRY DllMain(HMODULE hMOD, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//DisableThreadLibraryCalls(hMOD);
		AllocConsole();
		freopen("conin$", "r+t", stdin);
		freopen("conout$", "w+t", stdout);
		freopen("conout$", "w+t", stderr);
		CreateThread(0, 0, &CheatEntryPoint, 0, 0, 0);
	};
	}
	return TRUE;
}
