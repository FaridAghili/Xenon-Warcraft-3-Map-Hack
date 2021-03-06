#include "Warcraft.h"

extern DWORD GAME_PlayerIndex;

void GrayHpUnderFogInit()
{
	if (SettingGet("Gray HP Under Fog"))
		PlantDetourCall((BYTE *)dwGameDll + 0x364BF2, (BYTE *)GrayHpUnderFog, 5);
}

void __declspec(naked) GrayHpUnderFog()
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
		MOV  EAX, DWORD PTR DS:[EDX+0xFC]
		MOV  ECX, ESI
		CALL EAX
		CMP  EAX, 1
		JE   Visible

		POPAD

		MOV  EAX, DWORD PTR SS:[ESP+4]
		OR   DWORD PTR DS:[EAX], 0xFFFFFF
		MOV  DL, BYTE PTR DS:[EAX+3]
		MOV  BYTE PTR DS:[ECX+0x68], DL
		MOV  DL, BYTE PTR DS:[EAX]
		MOV  BYTE PTR DS:[ECX+0x69], DL
		MOV  DL, BYTE PTR DS:[EAX+1]
		MOV  BYTE PTR DS:[ECX+0x6A], DL
		MOV  DL, BYTE PTR DS:[EAX+2]
		MOV  BYTE PTR DS:[ECX+0x6B], DL

		MOV  EDX, DWORD PTR DS:[ECX]
		MOV  EAX, DWORD PTR DS:[EDX+0x24]
		CALL EAX
		RET  4
		
	Visible:
		POPAD

		MOV  EAX, DWORD PTR SS:[ESP+4]
		MOV  DL, BYTE PTR DS:[EAX+3]
		MOV  BYTE PTR DS:[ECX+0x68], DL
		MOV  DL, BYTE PTR DS:[EAX]
		MOV  BYTE PTR DS:[ECX+0x69], DL
		MOV  DL, BYTE PTR DS:[EAX+1]
		MOV  BYTE PTR DS:[ECX+0x6A], DL
		MOV  DL, BYTE PTR DS:[EAX+2]
		MOV  BYTE PTR DS:[ECX+0x6B], DL

		MOV  EDX, DWORD PTR DS:[ECX]
		MOV  EAX, DWORD PTR DS:[EDX+0x24]
		CALL EAX
		RET  4
	}
}