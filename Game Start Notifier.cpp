#include "Warcraft.h"

void GameStartNotifierInit()
{
	if (SettingGet("Game Start Notifier"))
		PlantDetourJump((BYTE *)dwGameDll + 0x5C0D81, (BYTE *)GameStartNotifier, 5);
}

void GameStartNotifier()
{
	if (GetForegroundWindow() != hWnd)
		ShowWindow(hWnd, SW_RESTORE);
}