#include "Warcraft.h"

void HideDll(HMODULE hModule)
{
	DWORD dwPEB_LDR_DATA = NULL;

	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
		mov eax, [eax+0Ch]
		mov dwPEB_LDR_DATA, eax

		//InLoadOrderModuleList:
			mov esi, [eax+0Ch]
			mov edx, [eax+10h]

		LoopInLoadOrderModuleList:
			lodsd
			mov esi, eax
			mov ecx, [eax+18h]
			cmp ecx, hModule
			jne SkipA
			mov ebx, [eax]
			mov ecx, [eax+4]
			mov [ecx], ebx
			mov [ebx+4], ecx
			jmp InMemoryOrderModuleList

		SkipA:
			cmp edx, esi
			jne LoopInLoadOrderModuleList

		InMemoryOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+14h]
			mov edx, [eax+18h]

		LoopInMemoryOrderModuleList:
			lodsd
			mov esi, eax
			mov ecx, [eax+10h]
			cmp ecx, hModule
			jne SkipB
			mov ebx, [eax]
			mov ecx, [eax+4]
			mov [ecx], ebx
			mov [ebx+4], ecx
			jmp InInitializationOrderModuleList

		SkipB:
			cmp edx, esi
			jne LoopInMemoryOrderModuleList

		InInitializationOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+1Ch]
			mov edx, [eax+20h]

		LoopInInitializationOrderModuleList:
			lodsd
			mov esi, eax
			mov ecx, [eax+08h]
			cmp ecx, hModule
			jne SkipC
			mov ebx, [eax]
			mov ecx, [eax+4]
			mov [ecx], ebx
			mov [ebx+4], ecx
			jmp Finished

		SkipC:
			cmp edx, esi
			jne LoopInInitializationOrderModuleList

		Finished:
			popfd;
			popad;
	}
}

void Patch(DWORD dwBaseAddress, char *szData, int iSize)
{
	DWORD dwOldProtection = NULL;
	
	VirtualProtect((LPVOID)dwBaseAddress, iSize, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	CopyMemory((LPVOID)dwBaseAddress, szData, iSize);
	VirtualProtect((LPVOID)dwBaseAddress, iSize, dwOldProtection, NULL);
}

void PlantDetourCall(BYTE *bSource, BYTE *bDestination, int iLength)
{
	DWORD dwOldProtection = NULL;

	BYTE *bJump = (BYTE *)malloc(iLength + 5);

	VirtualProtect(bSource, iLength, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	memcpy(bJump + 3, bSource, iLength);

	bJump[0] = 0x58;
	bJump[1] = 0x59;
	bJump[2] = 0x50;
	bJump[iLength + 3] = 0xE9;
	*(DWORD *)(bJump + iLength + 4) = (DWORD)((bSource + iLength) - (bJump + iLength + 3)) - 5;

	bSource[0] = 0xE8;
	*(DWORD *)(bSource + 1) = (DWORD)(bDestination - (bSource)) - 5;

	for (int i = 5; i < iLength; i++)
		bSource[i] = 0x90;

	VirtualProtect(bSource, iLength, dwOldProtection, NULL);
}

void PlantDetourJump(BYTE *bSource, BYTE *bDestination, int iLength)
{
	DWORD dwOldProtection = NULL;

	BYTE *bJump = (BYTE *)malloc(iLength + 5);

	VirtualProtect(bSource, iLength, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	memcpy(bJump, bSource, iLength);

	bJump[iLength] = 0xE9;
	*(DWORD *)(bJump + iLength) = (DWORD)((bSource + iLength) - (bJump + iLength)) - 5;

	bSource[0] = 0xE9;
	*(DWORD *)(bSource + 1) = (DWORD)(bDestination - bSource) - 5;

	for (int i = 5; i < iLength; i++)
		bSource[i] = 0x90;

	VirtualProtect(bSource, iLength, dwOldProtection, NULL);
}

void SettingInitialize()
{
	if (FileExists(".\\Xenon.ini"))
		return;
	
	SettingSet("Bypass -ah in DotA", "1");
	SettingSet("Enable Trade / Resource View", "1");
	SettingSet("Make Units Clickable", "1");
	SettingSet("Reveal Illusions", "1");
	SettingSet("Reveal Invisibles", "1");
	SettingSet("Reveal Units on Main Map", "1");
	SettingSet("Reveal Units on Mini Map", "1");
	SettingSet("Show Enemies Ping Signals", "1");
	SettingSet("Show Missiles", "1");
	SettingSet("Show Rally Points", "1");
	SettingSet("Show Runes", "1");
	SettingSet("Show Skills / Cooldowns", "1");
	SettingSet("Color Invisibles", "1");
	SettingSet("Damage Notifier", "1");
	SettingSet("Game Start Notifier", "1");
	SettingSet("Gray HP Under Fog", "1");
	SettingSet("Instant Game Start", "0");
	SettingSet("Mana Bar", "1");
	SettingSet("Roshan Notifier", "1");
	SettingSet("Rune Notifier", "1");
	SettingSet("SafeClick", "1");
	SettingSet("Show AS & MS in Number", "1");
	SettingSet("Show HP & MP Regen", "1");
}

void SettingSet(char *szKey, char *szValue)
{
	WritePrivateProfileString("Xenon", szKey, szValue, ".\\Xenon.ini");
}

bool SettingGet(char *szKey)
{
	return GetPrivateProfileInt("Xenon", szKey, 0, ".\\Xenon.ini") == 1;
}

bool FileExists(char *szFile)
{
  FILE *pFile;
  fopen_s(&pFile, szFile, "r");

  if (pFile != NULL)
  {
	  fclose(pFile);
	  return true;
  }

  return false;
}