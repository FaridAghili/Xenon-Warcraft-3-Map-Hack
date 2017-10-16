#include "Warcraft.h"

extern DWORD GAME_PlayerIndex;

DWORD dwColorUnit               = dwGameDll + 0x4D3220;
DWORD dwColorInvisiblesCall     = dwGameDll + 0x2AB710;
DWORD dwColorInvisiblesJumpBack = dwGameDll + 0x39999A;

void ColorInvisiblesInit()
{
	if (SettingGet("Color Invisibles"))
		PlantDetourJump((BYTE *)dwGameDll + 0x399995, (BYTE *)ColorInvisibles, 5);
}

void __declspec(naked) ColorInvisibles()
{
	__asm
	{
		PUSHAD

		MOV  EDX, GAME_PlayerIndex
		MOV  EDX, DWORD PTR DS:[EDX]
		XOR  EAX, EAX
		MOV  AL, BYTE PTR DS:[EDX+0x28]
		MOV  EDX, DWORD PTR DS:[ESI]

		PUSH 4
		PUSH 0
		PUSH EAX
		MOV	 EAX, DWORD PTR DS:[EDX+0xFC]
		MOV  ECX, ESI
		CALL EAX
		CMP  EAX, 1
		JE   Finish

		XOR  EAX, EAX
		MOV  AL, BYTE PTR DS:[ESI+0x5F]
		CMP  AL, 1
		JNZ  Finish

		MOV  ECX, ESI
		PUSH ECX
		MOV  EAX, ESP
		MOV  DWORD PTR DS:[EAX], 0xFFCC33CC
		MOV  ECX, DWORD PTR DS:[ECX+0x28]
		XOR  EDX, EDX
		CALL dwColorUnit

	Finish:
		POPAD
		CALL dwColorInvisiblesCall
		JMP  dwColorInvisiblesJumpBack
	}
}