#include "Warcraft.h"

extern GAME_PingMinimapEx PingMinimapEx;

DWORD dwRoshanNotifierCall     = dwGameDll + 0x3BD3B0;
DWORD dwRoshanNotifierJumpBack = dwGameDll + 0x3C52DC;

DWORD dwRoshanTemp1, dwRoshanTemp2, dwRoshanTemp3, dwRoshanTemp4,
	  dwRoshanTemp5, dwRoshanTemp6, dwRoshanTemp7, dwRoshanTemp8;

float fRoshanX        = 2450,
	  fRoshanY        = -730,
	  fRoshanDuration = 10;

void RoshanNotifierInit()
{
	if (SettingGet("Roshan Notifier"))
		PlantDetourJump((BYTE *)dwGameDll + 0x3C52D7, (BYTE *)RoshanNotifier, 5);
}

void __declspec(naked) RoshanNotifier()
{
	__asm
	{
		CALL	dwRoshanNotifierCall

		MOV		dwRoshanTemp1, EAX
		MOV		dwRoshanTemp2, EBX
		MOV		dwRoshanTemp3, ECX
		MOV		dwRoshanTemp4, EDX
		MOV		dwRoshanTemp5, ESI
		MOV		dwRoshanTemp6, EDI
		MOV		dwRoshanTemp7, EBP
		MOV		dwRoshanTemp8, ESP

		MOV		EAX, DWORD PTR DS:[ESP+0x10]
		CMP		EAX, 0x6E30304C
		JNE		Finish
	}

	if (!IsInGame())
		goto Finish;

	TextPrint("|CFFFCD211Xenon|R: |CFFDD8DFFRoshan|R respawned.", 10.0f);
	PingMinimapEx(&fRoshanX, &fRoshanY, &fRoshanDuration, 0xDD, 0x8D, 0xFF, false);
	
Finish:
	__asm
	{
		MOV		EAX, dwRoshanTemp1;
		MOV		EBX, dwRoshanTemp2;
		MOV		ECX, dwRoshanTemp3;
		MOV		EDX, dwRoshanTemp4;
		MOV		ESI, dwRoshanTemp5;
		MOV		EDI, dwRoshanTemp6;
		MOV		EBP, dwRoshanTemp7;
		MOV		ESP, dwRoshanTemp8;

		JMP		dwRoshanNotifierJumpBack;
	}
}