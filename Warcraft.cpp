#include "Warcraft.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		HideDll((HMODULE)dwGameDll);
		HideDll(hModule);

		if (WarcraftVersion() == 6401)
		{
			SettingInitialize();

			JassNativesInit();

			ColorInvisiblesInit();
			DamageNotifierInit();
			DreamUiInit();
			GameStartNotifierInit();
			GrayHpUnderFogInit();
			InstantGameStartInit();
			ManaBarInit();
			RoshanNotifierInit();
			RuneNotifierInit();
			SafeClickInit(true);

			HANDLE hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HotKeys, NULL, NULL, NULL);
			CloseHandle(hThread);
		}
	}

	return TRUE;
}