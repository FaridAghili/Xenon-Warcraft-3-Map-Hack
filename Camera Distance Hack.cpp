#include "Warcraft.h"

void CameraDistanceHack(int iKey)
{
	DWORD dwAddress = dwGameDll + 0x93645C;

	if (!IsInGame() || IsChatBoxOpen())
		return;

	DWORD dwOldProtection = NULL;

	switch (iKey)
	{
		case VK_ZoomIn:
			if (*(float *)dwAddress > 250)
			{
				VirtualProtect((LPVOID)dwAddress, sizeof(float), PAGE_EXECUTE_READWRITE, &dwOldProtection);
				*(float *)dwAddress -= 100;

				goto Update;
			}
			break;
		case VK_ZoomOut:
			if (*(float *)dwAddress < 3050)
			{
				VirtualProtect((LPVOID)dwAddress, sizeof(float), PAGE_EXECUTE_READWRITE, &dwOldProtection);
				*(float *)dwAddress += 100;

				goto Update;
			}
			break;
		case VK_Default:
			if (*(float *)dwAddress != 1650)
			{
				VirtualProtect((LPVOID)dwAddress, sizeof(float), PAGE_EXECUTE_READWRITE, &dwOldProtection);
				*(float *)dwAddress = 1650;

				goto Update;
			}
			break;
	}

	return;

Update:
	VirtualProtect((LPVOID)dwAddress, sizeof(float), dwOldProtection, NULL);

	TextPrintEx("|CFFFCD211Xenon|R: Camera Distance changed to %.0f", *(float *)dwAddress);

	PostMessage(hWnd, WM_SYSKEYDOWN, VK_PRIOR, NULL);
	PostMessage(hWnd, WM_SYSKEYDOWN, VK_NEXT, NULL);
}