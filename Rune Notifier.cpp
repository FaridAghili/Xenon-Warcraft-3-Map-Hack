#include "Warcraft.h"

extern GAME_PingMinimapEx PingMinimapEx;

DWORD dwRuneNotifierJumpBack = dwGameDll + 0x3BB9AC;

DWORD dwRuneEAX, dwRuneEBX, dwRuneECX, dwRuneEDX,
	  dwRuneESI, dwRuneEDI, dwRuneEBP, dwRuneESP;

float fRuneTopX     = -2400,
	  fRuneTopY     = 1600,
	  fRuneBotX     = 2970,
	  fRuneBotY     = -2850,
	  fRuneDuration = 10;

void RuneNotifierInit()
{
	if (SettingGet("Rune Notifier"))
		PlantDetourJump((BYTE *)dwGameDll + 0x3BB9A0, (BYTE *)RuneNotifier, 10);
}

void __declspec(naked) RuneNotifier()
{
	__asm
	{
		MOV		EAX, DWORD PTR SS:[ESP+0xC]
		MOV		EDX, DWORD PTR SS:[ESP+8]
		MOV		ECX, DWORD PTR SS:[ESP+4]

		MOV		dwRuneEAX, EAX
		MOV		dwRuneEBX, EBX
		MOV		dwRuneECX, ECX
		MOV		dwRuneEDX, EDX
		MOV		dwRuneESI, ESI
		MOV		dwRuneEDI, EDI
		MOV		dwRuneEBP, EBP
		MOV		dwRuneESP, ESP

		CMP		DWORD PTR DS:[EAX], 0x44CE0000
		JE		Top
		CMP		DWORD PTR DS:[EAX], 0xC5310000
		JE		Bot

		JMP		dwRuneNotifierJumpBack

	Top:
		CMP		ECX, 0x49303037
		JE		IllusionTop
		CMP		ECX, 0x49303036
		JE		HasteTop
		CMP		ECX, 0x4930304B
		JE		DoubleDamageTop
		CMP		ECX, 0x49303038
		JE		RegenerationTop
		CMP		ECX, 0x4930304A
		JE		InvisibilityTop
		JMP		dwRuneNotifierJumpBack

	Bot:
		CMP		ECX, 0x49303037
		JE		IllusionBot
		CMP		ECX, 0x49303036
		JE		HasteBot
		CMP		ECX, 0x4930304B
		JE		DoubleDamageBot
		CMP		ECX, 0x49303038
		JE		RegenerationBot
		CMP		ECX, 0x4930304A
		JE		InvisibilityBot
		JMP		dwRuneNotifierJumpBack
	}

	IllusionTop:
		TextPrint("|CFFFCD211Xenon|R: |CFFFFFC01Illusion|R rune spawned at the top spot.", 10.0f);
		PingMinimapEx(&fRuneTopX, &fRuneTopY, &fRuneDuration, 0xFF, 0xFC, 0x01, false);
		goto Finish;
	IllusionBot:
		TextPrint("|CFFFCD211Xenon|R: |CFFFFFC01Illusion|R rune spawned at the bottom spot.", 10.0f);
		PingMinimapEx(&fRuneBotX, &fRuneBotY, &fRuneDuration, 0xFF, 0xFC, 0x01, false);
		goto Finish;

	HasteTop:
		TextPrint("|CFFFCD211Xenon|R: |CFFFF0303Haste|R rune spawned at the top spot.", 10.0f);
		PingMinimapEx(&fRuneTopX, &fRuneTopY, &fRuneDuration, 0xFF, 0x03, 0x03, false);
		goto Finish;
	HasteBot:
		TextPrint("|CFFFCD211Xenon|R: |CFFFF0303Haste|R rune spawned at the bottom spot.", 10.0f);
		PingMinimapEx(&fRuneBotX, &fRuneBotY, &fRuneDuration, 0xFF, 0x03, 0x03, false);
		goto Finish;

	DoubleDamageTop:
		TextPrint("|CFFFCD211Xenon|R: |CFF0042FFDouble Damage|R rune spawned at the top spot.", 10.0f);
		PingMinimapEx(&fRuneTopX, &fRuneTopY, &fRuneDuration, 0x00, 0x42, 0xFF, false);
		goto Finish;
	DoubleDamageBot:
		TextPrint("|CFFFCD211Xenon|R: |CFF0042FFDouble Damage|R rune spawned at the bottom spot.", 10.0f);
		PingMinimapEx(&fRuneBotX, &fRuneBotY, &fRuneDuration, 0x00, 0x42, 0xFF, false);
		goto Finish;

	RegenerationTop:
		TextPrint("|CFFFCD211Xenon|R: |CFF00FF00Regeneration|R rune spawned at the top spot.", 10.0f);
		PingMinimapEx(&fRuneTopX, &fRuneTopY, &fRuneDuration, 0x00, 0xFF, 0x00, false);
		goto Finish;
	RegenerationBot:
		TextPrint("|CFFFCD211Xenon|R: |CFF00FF00Regeneration|R rune spawned at the bottom spot.", 10.0f);
		PingMinimapEx(&fRuneBotX, &fRuneBotY, &fRuneDuration, 0x00, 0xFF, 0x00, false);
		goto Finish;

	InvisibilityTop:
		TextPrint("|CFFFCD211Xenon|R: |CFF99CCFFInvisibility|R rune spawned at the top spot.", 10.0f);
		PingMinimapEx(&fRuneTopX, &fRuneTopY, &fRuneDuration, 0x99, 0xCC, 0xFF, false);
		goto Finish;
	InvisibilityBot:
		TextPrint("|CFFFCD211Xenon|R: |CFF99CCFFInvisibility|R rune spawned at the bottom spot.", 10.0f);
		PingMinimapEx(&fRuneBotX, &fRuneBotY, &fRuneDuration, 0x99, 0xCC, 0xFF, false);
		goto Finish;

Finish:
	__asm
	{
		MOV		EAX, dwRuneEAX
		MOV		EBX, dwRuneEBX
		MOV		ECX, dwRuneECX
		MOV		EDX, dwRuneEDX
		MOV		ESI, dwRuneESI
		MOV		EDI, dwRuneEDI
		MOV		EBP, dwRuneEBP
		MOV		ESP, dwRuneESP
		
		JMP		dwRuneNotifierJumpBack
	}
}