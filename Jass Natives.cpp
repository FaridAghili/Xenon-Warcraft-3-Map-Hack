#include "Warcraft.h"

DWORD GAME_PlayerIndex = dwGameDll + 0xAB65F4;

GAME_FogEnable            FogEnable;
GAME_FogMaskEnable        FogMaskEnable;
GAME_PingMinimapEx        PingMinimapEx;
GAME_ClearTextMessages    ClearTextMessages;
GAME_PauseGame            PauseGame;
GAME_GetLocalPlayer       GetLocalPlayer;
GAME_GetTriggerUnit       GetTriggerUnit;
GAME_IsUnitOwnedByPlayer  IsUnitOwnedByPlayer;
GAME_CreateTextTag        CreateTextTag;
GAME_SetTextTagPosUnit    SetTextTagPosUnit;
GAME_SetTextTagColor      SetTextTagColor;
GAME_SetTextTagVelocity   SetTextTagVelocity;
GAME_SetTextTagVisibility SetTextTagVisibility;
GAME_SetTextTagPermanent  SetTextTagPermanent;
GAME_SetTextTagLifespan   SetTextTagLifespan;
GAME_SetTextTagFadepoint  SetTextTagFadepoint;

void SetTextTagText(int t, char *s, float *height)
{
	DWORD dwAddress = dwGameDll + 0x426CF0;

	__asm
	{
		MOV		ECX, dwGameDll
		MOV		ECX, DWORD PTR DS:[ECX+0xAB65F4]
		LEA		ECX, [ECX+0x1C]
		MOV		ECX, DWORD PTR DS:[ECX]

		MOV		EAX, height
		MOV		EAX, DWORD PTR DS:[EAX]
		PUSH	EAX
		PUSH	s
		PUSH	t
		CALL	dwAddress
	}
}

DWORD dwGetUnitNameA = dwGameDll + 0x3BDCB0;
DWORD dwGetUnitNameB = dwGameDll + 0x32DBE0;

char __declspec(naked) *GetUnitName(DWORD hUnit)
{
	__asm
	{
		MOV		ECX, [ESP+0x4]
		CALL	dwGetUnitNameA
		TEST	EAX, EAX
		JZ		RETURN

		MOV		ECX, [EAX+0x30]
		XOR		EDX, EDX
		CALL	dwGetUnitNameB

	RETURN:
		RETN
	}
}

DWORD dwGetItemNameA = dwGameDll + 0x3BEB50;
DWORD dwGetItemNameB = dwGameDll + 0x32DBE0;

char __declspec(naked) *GetItemName(DWORD hItem)
{
	__asm
	{
		MOV		ECX, [ESP+0x4]
		CALL	dwGetItemNameA
		TEST	EAX, EAX
		JZ		RETURN

		MOV		ECX, [EAX+0x30]
		XOR		EDX, EDX
		CALL	dwGetItemNameB

	RETURN:
		RETN
	}
}

void IntToRawCode(long int num, char *cToCopy)
{
	cToCopy[0] = reinterpret_cast<char*>(&num)[3];
	cToCopy[1] = reinterpret_cast<char*>(&num)[2];
	cToCopy[2] = reinterpret_cast<char*>(&num)[1];
	cToCopy[3] = reinterpret_cast<char*>(&num)[0];
	cToCopy[4] = 0;

	return;
}

bool IsItem(DWORD dwItemHandle, char *szItemName)
{
	return strcmp(GetItemName(dwItemHandle), szItemName) == 0;
}

void JassNativesInit()
{
	FogEnable            = (GAME_FogEnable)           (dwGameDll + 0x3BB1E0); 
	FogMaskEnable        = (GAME_FogMaskEnable)       (dwGameDll + 0x3BB210);
	PingMinimapEx        = (GAME_PingMinimapEx)       (dwGameDll + 0x3B8660);
	ClearTextMessages    = (GAME_ClearTextMessages)   (dwGameDll + 0x3B4E60);
	PauseGame            = (GAME_PauseGame)           (dwGameDll + 0x3BC4D0);
	GetLocalPlayer       = (GAME_GetLocalPlayer)      (dwGameDll + 0x3BBB60);
	GetTriggerUnit       = (GAME_GetTriggerUnit)      (dwGameDll + 0x3BB240);
	IsUnitOwnedByPlayer  = (GAME_IsUnitOwnedByPlayer) (dwGameDll + 0x3C7A30);
	CreateTextTag        = (GAME_CreateTextTag)       (dwGameDll + 0x3BC580);
	SetTextTagPosUnit    = (GAME_SetTextTagPosUnit)   (dwGameDll + 0x3CB890);
	SetTextTagColor      = (GAME_SetTextTagColor)     (dwGameDll + 0x3BC6A0);
	SetTextTagVelocity   = (GAME_SetTextTagVelocity)  (dwGameDll + 0x3BC700);
	SetTextTagVisibility = (GAME_SetTextTagVisibility)(dwGameDll + 0x3BC760);
	SetTextTagPermanent  = (GAME_SetTextTagPermanent) (dwGameDll + 0x3BC7C0);
	SetTextTagLifespan   = (GAME_SetTextTagLifespan)  (dwGameDll + 0x3BC820);
	SetTextTagFadepoint  = (GAME_SetTextTagFadepoint) (dwGameDll + 0x3BC850);
}