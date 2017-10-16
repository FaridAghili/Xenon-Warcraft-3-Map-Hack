#include "Warcraft.h"

DWORD Storm503 = dwGameDll + 0x6EB5BE;
DWORD Storm578 = dwGameDll + 0x6EB5A6;
DWORD GetRegen = 0xAB7788;

char *AsFormat   = "%0.02f";
char *MsFormat   = "%.0f";
char *HpMpFormat = "%s\n|CFFF9D112HP/s:|r |CFF00FF00%.02f|r\n|CFFF9D112MP/s:|r |CFFC3DBFF%.02f|r";

float HpRegen, MpRegen;

void DreamUiInit()
{
	DWORD dwOldProtection = NULL;

	// Show AS & MS in Number
	if (SettingGet("Show AS & MS in Number"))
	{
		VirtualProtect((LPVOID)(dwGameDll + 0x339000), 534000, PAGE_EXECUTE_READWRITE, &dwOldProtection);
		*(DWORD *) (dwGameDll + 0x33911C) = (DWORD)MsToInt - (dwGameDll + 0x339120);
		*(DWORD *) (dwGameDll + 0x3392BC) = (DWORD)AsToInt - (dwGameDll + 0x3392C0);
		VirtualProtect((LPVOID)(dwGameDll + 0x339000), 534000, dwOldProtection, NULL);
	}

	// Show HP & MP Regen
	if (SettingGet("Show HP & MP Regen"))
	{
		VirtualProtect((LPVOID)(dwGameDll + 0x358000), 515000, PAGE_EXECUTE_READWRITE, &dwOldProtection);
		*(BYTE *)(dwGameDll + 0x358137) = 0xE8;
		*(DWORD *) (dwGameDll + 0x358138) = (DWORD)GetHpRegen - (dwGameDll + 0x35813C);
		*(BYTE *)(dwGameDll + 0x35813C) = 0x90;
		*(BYTE *)(dwGameDll + 0x35813D) = 0x90;
		*(BYTE *)(dwGameDll + 0x358322) = 0xE8;
		*(DWORD *) (dwGameDll + 0x358323) = (DWORD)GetMpRegen - (dwGameDll + 0x358327);
		*(BYTE *)(dwGameDll + 0x358327) = 0x90;
		VirtualProtect((LPVOID)(dwGameDll + 0x358000), 515000, dwOldProtection, NULL);

		VirtualProtect((LPVOID)(dwGameDll + 0x354B0C), 6, PAGE_EXECUTE_READWRITE, &dwOldProtection);
		*(BYTE *)(dwGameDll + 0x354B0C) = 0xE8;
		*(DWORD *) (dwGameDll + 0x354B0D) = (DWORD)ShowText - (dwGameDll + 0x354B11);
		*(BYTE *)(dwGameDll + 0x354B11) = 0x90;
		VirtualProtect((LPVOID)(dwGameDll + 0x354B0C), 6, dwOldProtection, NULL);
	}
}

void __declspec(naked) GetHpRegen()
{
	_asm
	{
		LEA  EAX, [ESP+0x0D8]

		PUSH EAX
		PUSH ECX
		PUSH ESI

		ADD  ECX, 0x98
		MOV  ECX, DWORD PTR DS:[ECX+8]
		MOV  ESI, dwGameDll
		MOV  EAX, GetRegen
		MOV  ESI, DWORD PTR DS:[ESI+EAX]
		MOV  EAX, DWORD PTR DS:[ESI+0x0C]
		MOV  ECX, DWORD PTR DS:[ECX*8+EAX+4]
		MOV  ECX, DWORD PTR DS:[ECX+0x7C]
		MOV  HpRegen, ECX

		POP  ESI
		POP  ECX
		POP  EAX

		RETN
	}
}

void __declspec(naked) GetMpRegen()
{
	_asm
	{
		ADD  ECX, 0x0B8

		PUSH EAX
		PUSH ECX
		PUSH ESI

		MOV  ECX, DWORD PTR DS:[ECX+8]
		MOV  ESI, dwGameDll
		MOV  EAX, GetRegen
		MOV  ESI, DWORD PTR DS:[ESI+EAX]
		MOV  EAX, DWORD PTR DS:[ESI+0x0C]
		MOV  ECX, DWORD PTR DS:[ECX*8+EAX+4]
		MOV  ECX, DWORD PTR DS:[ECX+0x7C]
		MOV  MpRegen, ECX

		POP  ESI
		POP  ECX
		POP  EAX

		RETN
	}
}

void __declspec(naked) AsToInt()
{
	DWORD dwAsToIntBuffer;

	_asm
	{
		MOV  EAX, DWORD PTR DS:[ESP]
		MOV  dwAsToIntBuffer, EAX

		FLD  DWORD PTR SS:[ESP+0x6C]
		SUB  ESP, 8
		FSTP QWORD PTR SS:[ESP]
		PUSH AsFormat
		PUSH 7
		PUSH ECX
		CALL Storm578

		ADD  ESP, 0x18

		CALL Storm503
		PUSH dwAsToIntBuffer

		RETN
	}
}

void __declspec(naked) MsToInt()
{
	DWORD dwMsToIntBuffer;

	_asm
	{
		MOV  EAX, DWORD PTR DS:[ESP]
		MOV  dwMsToIntBuffer, EAX

		FLD  DWORD PTR SS:[ESP+0x90]
		SUB  ESP, 8
		FSTP QWORD PTR SS:[ESP]
		PUSH MsFormat
		PUSH 7
		PUSH ECX
		CALL Storm578

		ADD  ESP, 0x18

		CALL Storm503
		PUSH dwMsToIntBuffer

		RETN
	}
}

void __declspec(naked) ShowText()
{
	_asm
	{
		PUSH ECX
		LEA  ECX, [ESP+0x30]
		FLD  MpRegen
		FLD  HpRegen
		SUB  ESP, 0x10
		FSTP QWORD PTR SS:[ESP]
		FSTP QWORD PTR SS:[ESP+8]
		PUSH ECX
		PUSH HpMpFormat
		PUSH 0x80
		PUSH ECX
		CALL Storm578;
		ADD  ESP, 0x20
		POP  ECX
		MOV  EDI, [EBP+0x134]
		RETN
	}
}