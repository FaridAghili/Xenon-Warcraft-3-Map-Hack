#include "Warcraft.h"

extern GAME_GetLocalPlayer GetLocalPlayer;
extern GAME_GetTriggerUnit GetTriggerUnit;
extern GAME_IsUnitOwnedByPlayer IsUnitOwnedByPlayer;

extern GAME_CreateTextTag CreateTextTag;
extern GAME_SetTextTagPosUnit SetTextTagPosUnit;
extern GAME_SetTextTagColor SetTextTagColor;
extern GAME_SetTextTagVelocity SetTextTagVelocity;
extern GAME_SetTextTagVisibility SetTextTagVisibility;
extern GAME_SetTextTagPermanent SetTextTagPermanent;
extern GAME_SetTextTagLifespan SetTextTagLifespan;
extern GAME_SetTextTagFadepoint SetTextTagFadepoint;

float height       = 0.03f,
	  heightOffset = 0.0f,
	  xvel         = 0.0f,
	  yvel         = 0.1f,
	  fadepoint    = 0.1f,
	  lifespan     = 0.75f;

float fDamageValue;
DWORD dwReturnAddress;
char  szDamageValue[16];
DWORD hTextTag;

void DamageNotifierInit()
{
	if (SettingGet("Damage Notifier"))
		PlantDetourCall((BYTE *)dwGameDll + 0x3C3C58, (BYTE *)DamageNotifier, 5);
}

void __declspec(naked) DamageNotifier()
{
	__asm
	{
		MOV fDamageValue, EAX
		MOV EAX, [ESP+4]
		MOV dwReturnAddress, EAX
	}

	if ((dwReturnAddress < dwGameDll) || (dwReturnAddress > (dwGameDll + 0x0086C000)))
		goto RETN;

	if (fDamageValue < 1.0f)
		goto RETN;

	if (!IsUnitOwnedByPlayer(GetTriggerUnit(), GetLocalPlayer()))
		goto RETN;

	sprintf_s(szDamageValue, "%d", (int)fDamageValue);

	hTextTag = CreateTextTag();
	SetTextTagText(hTextTag, szDamageValue, &height);
	SetTextTagPosUnit(hTextTag, GetTriggerUnit(), &heightOffset);
	SetTextTagColor(hTextTag, 255, 0, 0, 255);
	SetTextTagVelocity(hTextTag, &xvel, &yvel);
	SetTextTagFadepoint(hTextTag, &fadepoint);
	SetTextTagLifespan(hTextTag, &lifespan);
	SetTextTagPermanent(hTextTag, false);
	SetTextTagVisibility(hTextTag, true);

RETN:
	__asm
	{
		MOV EAX, fDamageValue
		JMP dwReturnAddress
	}
}