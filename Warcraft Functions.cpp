#include "Warcraft.h"

DWORD GAME_GlobalClass   = dwGameDll + 0xAB4F80;
DWORD GAME_PrintToScreen = dwGameDll + 0x2F8E40;

void SetTls()
{
	DWORD Data = *(DWORD *)(dwGameDll + 0xACEB4C);
	DWORD TlsIndex = *(DWORD *)(dwGameDll + 0xAB7BF4);

	if (TlsIndex)
	{
		DWORD v5 = **(DWORD **)(*(DWORD *)(*(DWORD *)(dwGameDll + 0xACEB5C) + 4 * Data) + 44);
		TlsSetValue(TlsIndex, *(LPVOID *)(v5 + 520));
	}
}

void TextPrint(char *szText, float fDuration)
{
	DWORD dwDuration = *((DWORD *)&fDuration);

	__asm
	{
		PUSH	0xFFFFFFFF
		PUSH	dwDuration
		PUSH	szText
		PUSH	0x0
		PUSH	0x0
		MOV		ECX, [GAME_GlobalClass]
		MOV		ECX, [ECX]
		CALL	GAME_PrintToScreen
	}
}

void TextPrintEx(char *szText, ...)
{
	char szTextEx[8192] = {NULL};

	va_list Args;
	va_start(Args, szText);
	vsprintf_s(szTextEx, szText, Args);
	va_end(Args);

	TextPrint(szTextEx);
}

DWORD WarcraftVersion()
{
	DWORD dwHandle = NULL;
	DWORD dwLen    = GetFileVersionInfoSize("Game.dll", &dwHandle);

	LPVOID lpData = new char[dwLen];
	GetFileVersionInfo("Game.dll", dwHandle, dwLen, lpData);

	LPBYTE lpBuffer = NULL;
	UINT   uLen     = NULL;
	VerQueryValue(lpData, "\\", (LPVOID *)&lpBuffer, &uLen);

	VS_FIXEDFILEINFO *Version = (VS_FIXEDFILEINFO *)lpBuffer;

	return LOWORD(Version->dwFileVersionLS);
}