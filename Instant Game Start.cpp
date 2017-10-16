#include "Warcraft.h"

void InstantGameStartInit()
{
	if (SettingGet("Instant Game Start"))
		InstantGameStart();
}

void InstantGameStart()
{
	DWORD dwAddress       = dwGameDll + 0x95FBB4;
	DWORD dwOldProtection = NULL;

	VirtualProtect((LPVOID)dwAddress, sizeof(float), PAGE_EXECUTE_READWRITE, &dwOldProtection);
	*(float *)dwAddress = 0.1f;
	VirtualProtect((LPVOID)dwAddress, sizeof(float), dwOldProtection, NULL);
}