#include "Warcraft.h"

bool IsChatBoxOpen()
{
	return *(bool *)(dwGameDll + 0xAD15F0);
}

bool IsInGame()
{
	return *(DWORD *)(dwGameDll + 0xAB573C) == 4 && *(DWORD *)(dwGameDll + 0xAB5738) == 4;
}