#include "Warcraft.h"

void ScoreboardShortcutKey()
{
	if (!IsInGame())
		return;

	DWORD dwOldProtection = NULL;

	DWORD dwPointerOffsets[5] = {0x44, 0x2D4, 0x0, 0x0, 0x14};
	DWORD dwAddress = CalculatePointers(dwGameDll + 0xAAE314, dwPointerOffsets);

	VirtualProtect((LPVOID)dwAddress, sizeof(bool), PAGE_EXECUTE_READWRITE, &dwOldProtection);
	*(bool *)dwAddress = !*(bool *)dwAddress;
	VirtualProtect((LPVOID)dwAddress, sizeof(bool), dwOldProtection, NULL);
}

DWORD CalculatePointers(DWORD dwOffset, DWORD dwPointerOffsets[5])
{
	for (int i = 0; i <= 4; i++)
	{
		dwOffset = *(DWORD *)dwOffset;
		dwOffset += dwPointerOffsets[i];
	}

	return dwOffset;
}