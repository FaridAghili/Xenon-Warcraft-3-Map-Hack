#include "Warcraft.h"

bool bIsSafeClickEnable = false;

typedef bool(__thiscall *CUnit_IsUnitVisible_t)(CUnit *, DWORD, DWORD, DWORD);
CUnit_IsUnitVisible_t CUnit_IsUnitVisible = CUnit_IsUnitVisible_t(dwGameDll + 0x285080);

typedef DWORD(__thiscall *GetTlsData_t)(int nYea);
GetTlsData_t GetTlsData = GetTlsData_t(dwGameDll + 0x4C34D0);

CGameWar3 *GameWar3 = (CGameWar3 *)*(DWORD *)(dwGameDll + 0xACD44C);
DWORD UnitArray_v = dwGameDll + 0xACE66C;

void SafeClickInit(bool bIsInit)
{
	if (bIsInit)
	{
		if (SettingGet("SafeClick"))
		{
			PlantDetourCall((BYTE *)dwGameDll + 0x54D97F, (BYTE *)(DWORD_PTR)SendAction_interception, 5);
			bIsSafeClickEnable = true;
		}

		return;
	}

	if (!bIsSafeClickEnable)
	{
		PlantDetourCall((BYTE *)dwGameDll + 0x54D97F, (BYTE *)(DWORD_PTR)SendAction_interception, 5);
		TextPrint("|CFFFCD211Xenon|R: SafeClick turned |CFF00FF00On|R.");
		bIsSafeClickEnable = true;
	}
	else
	{
		Patch(dwGameDll + 0x54D97F, "\xE8\x4C\x5B\xF7\xFF", 5);
		TextPrint("|CFFFCD211Xenon|R: SafeClick turned |CFFFF0000Off|R.");
		bIsSafeClickEnable = false;
	}
}

class CAction {
	void *vft;
	BYTE *pbData;

public:
	inline BYTE * GetData()	{ return pbData; }
};

struct SelectionAction_t {
	BYTE bOpCode;
	BYTE bMode;
	WORD wCount;
	DWORD dwUnitIds[12][2];
};

class CGameWar3 {
	BYTE _0[0x28];
	WORD m_wLocalPlayerIndex;

public:
	inline int GetLocalPlayerSlot() { return m_wLocalPlayerIndex; }
};

class CUnit {
	BYTE _0[0xC];
	DWORD m_dwId1;
	DWORD m_dwId2;

public:
	inline DWORD GetId1() { return m_dwId1; }

	inline DWORD GetId2() { return m_dwId2; }

	bool IsVisibleToPlayer(int nPlayerIndex)
	{
		return CUnit_IsUnitVisible(this, nPlayerIndex, 0, 4);
	}

	static CUnit *GetUnitByIDs(DWORD dwId1, DWORD dwId2)
	{
		CUnit** lpUnits = (CUnit **)*(DWORD *)(*(DWORD *)(*(DWORD *)UnitArray_v + 0x3BC) + 0x608);
		int nCount = (int)*(DWORD *)(*(DWORD *)(*(DWORD *)UnitArray_v + 0x3BC) + 0x604);

		for (int i = 0; i < nCount; i++)
			if (lpUnits[i]->GetId1() == dwId1 && lpUnits[i]->GetId2() == dwId2)
				return lpUnits[i];

		return 0;
	}
};

void __declspec(naked) SendAction_interception()
{
	__asm
	{
		push ebx
		call SendAction_Hook
		test eax,eax
		jz   dontsend

		mov	 eax, 4C34D0h
		add  eax, dwGameDll
		mov  ecx, 0Dh
		call eax
		retn

	dontsend:
		pop  eax
		pop  edi
		pop  esi
		pop  ebx
		add  esp, 0Ch
		retn
	}
}

bool __stdcall SendAction_Hook(CAction *lpAction)
{
	if (*(DWORD *)(*(DWORD* )(*(DWORD *)(GetTlsData(0xD) + 0x10) + 8) + 0x278) != 4)
		return true;

	if (lpAction->GetData()[0] == 0x16)
	{
		GameWar3 = (CGameWar3 *)*(DWORD *)(dwGameDll + 0xAB65F4);

		SelectionAction_t *SelectionAction;

		SelectionAction = (SelectionAction_t *)lpAction->GetData();

		if (SelectionAction->wCount == 1 && SelectionAction->bMode == 1)
		{
			if (CUnit::GetUnitByIDs(SelectionAction->dwUnitIds[0][0], SelectionAction->dwUnitIds[0][1]) &&
			!CUnit::GetUnitByIDs(SelectionAction->dwUnitIds[0][0], SelectionAction->dwUnitIds[0][1])->IsVisibleToPlayer(GameWar3->GetLocalPlayerSlot()))
				return false;
		}
		else
			return true;
	}

	return true;
}