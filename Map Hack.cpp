#include "Warcraft.h"

bool bIsMapHackEnable = false;
int  iMode = 0;

void MapHack(bool bStealth)
{
	if (!IsInGame())
		return;

	if (!bIsMapHackEnable)
	{
		bIsMapHackEnable = true;

		// Bypass -ah in DotA
		if (SettingGet("Bypass -ah in DotA"))
		{
			Patch(dwGameDll + 0x3C639C, "\xB8", 1);
			Patch(dwGameDll + 0x3C63A1, "\xEB", 1);
			Patch(dwGameDll + 0x3CB872, "\xEB", 1);
		}

		// Enable Enable Trade / Resource View
		if (SettingGet("Enable Enable Trade / Resource View"))
		{
			Patch(dwGameDll + 0x34DDA2, "\xB8\xC8\x00\x00\x00\x90", 6);
			Patch(dwGameDll + 0x34DDAA, "\xB8\x64\x00\x00\x00\x90", 6);
			Patch(dwGameDll + 0x35FA4A, "\x90\x90", 2);
		}

		// Make Units Clickable
		if (SettingGet("Make Units Clickable"))
			Patch(dwGameDll + 0x2851B2, "\xEB", 1);

		// Reveal Illusions
		if (SettingGet("Reveal Illusions"))
			Patch(dwGameDll + 0x282A5C, "\x40\xC3", 2);

		// Reveal Invisibles
		if (SettingGet("Reveal Invisibles"))
			Patch(dwGameDll + 0x399A98, "\xEB", 1);

		// Reveal Units on Main Map
		if (SettingGet("Reveal Units on Main Map"))
		{
			Patch(dwGameDll + 0x3A159B, "\x90\x90", 2);
			Patch(dwGameDll + 0x361176, "\xEB", 1); // Creep Dots
		}

		// Reveal Units on Mini Map
		if (SettingGet("Reveal Units on Mini Map"))
			Patch(dwGameDll + 0x36143C, "\x00", 1);

		// Show Enemies Ping Signals
		if (SettingGet("Show Enemies Ping Signals"))
		{
			Patch(dwGameDll + 0x43EE96, "\x3B", 1);
			Patch(dwGameDll + 0x43EE99, "\x85", 1);
			Patch(dwGameDll + 0x43EEA9, "\x3B", 1);
			Patch(dwGameDll + 0x43EEAC, "\x85", 1);
		}

		// Show Missiles
		if (SettingGet("Show Missiles"))
		{
			Patch(dwGameDll + 0x38E9F1, "\xFF", 1);
		}

		// Show Rally Points
		if (SettingGet("Show Rally Points"))
		{
			Patch(dwGameDll + 0x04B7D3, "\x90\x90", 2);
		}

		// Show Runes
		if (SettingGet("Show Runes"))
		{
			Patch(dwGameDll + 0x3A14DB, "\xEB", 1);
		}

		// Show Skills / Cooldowns
		if (SettingGet("Show Skills / Cooldowns"))
		{
			Patch(dwGameDll + 0x2026DC, "\x90\x90\x90\x90\x90\x90", 6);
			Patch(dwGameDll + 0x0C838D, "\x8C", 1);
			Patch(dwGameDll + 0x28E1DE, "\xEB", 1);
			Patch(dwGameDll + 0x34F2A8, "\x90\x90", 2);
			Patch(dwGameDll + 0x34F2E9, "\x00", 1);
		}

		if (bStealth)
			return;

		TextPrint("|CFFFCD211Xenon|R: Map Hack turned |CFF00FF00On|R.");
	}
	else
	{
		bIsMapHackEnable = false;

		// Bypass -ah in DotA
		Patch(dwGameDll + 0x3C639C, "\x3D", 1);
		Patch(dwGameDll + 0x3C63A1, "\x76", 1);
		Patch(dwGameDll + 0x3CB872, "\x74", 1);

		// Enable Enable Trade / Resource View
		Patch(dwGameDll + 0x34DDA2, "\x8B\x87\x6C\x01\x00\x00", 6);
		Patch(dwGameDll + 0x34DDAA, "\x8B\x87\x68\x01\x00\x00", 6);
		Patch(dwGameDll + 0x35FA4A, "\xEB\x08", 2);

		// Make Units Clickable
		Patch(dwGameDll + 0x2851B2, "\x75", 1);

		// Remove FOG on Main Map
		Patch(dwGameDll + 0x74C9F1, "\x8B\x54\x24\x28\x52", 5);
		Patch(dwGameDll + 0x3564B8, "\x66\x23\xC2", 3);
		iMode = 0;

		// Reveal Illusions
		Patch(dwGameDll + 0x282A5C, "\xC3\xCC", 2);

		// Reveal Invisibles
		Patch(dwGameDll + 0x399A98, "\x74", 1);

		// Reveal Units on Main Map
		Patch(dwGameDll + 0x3A159B, "\x23\xCA", 2);
		Patch(dwGameDll + 0x361176, "\x75", 1); // Creep Dots

		// Reveal Units on Mini Map
		Patch(dwGameDll + 0x36143C, "\x01", 1);

		// Show Enemies Ping Signals
		Patch(dwGameDll + 0x43EE96, "\x85", 1);
		Patch(dwGameDll + 0x43EE99, "\x84", 1);
		Patch(dwGameDll + 0x43EEA9, "\x85", 1);
		Patch(dwGameDll + 0x43EEAC, "\x84", 1);

		// Show Missiles
		Patch(dwGameDll + 0x38E9F1, "\x04", 1);

		// Show Rally Points
		Patch(dwGameDll + 0x04B7D3, "\x74\x5B", 2);

		// Show Runes
		Patch(dwGameDll + 0x3A14DB, "\x75", 1);

		// Show Skills / Cooldowns
		Patch(dwGameDll + 0x2026DC, "\x0F\x84\x5F\x01\x00\x00", 6);
		Patch(dwGameDll + 0x0C838D, "\x84", 1);
		Patch(dwGameDll + 0x28E1DE, "\x75", 1);
		Patch(dwGameDll + 0x34F2A8, "\x74\x08", 2);
		Patch(dwGameDll + 0x34F2E9, "\x08", 1);

		TextPrint("|CFFFCD211Xenon|R: Map Hack turned |CFFFF0000Off|R.");
	}
}

void ToggleFogOfWar()
{
	if (!IsInGame())
		return;

	if (!bIsMapHackEnable)
	{
		TextPrint("|CFFFCD211Xenon|R: Cannot toggle Fog of War while Map Hack is |CFFFF0000Off|R.");
		return;
	}

	iMode++;
	if (iMode == 3)
		iMode = 0;

	switch (iMode)
	{
	case 0:
		Patch(dwGameDll + 0x74C9F1, "\x8B\x54\x24\x28\x52", 5);
		Patch(dwGameDll + 0x3564B8, "\x66\x23\xC2", 3);
		TextPrint("|CFFFCD211Xenon|R: Fog of War has changed to |CFFFF0000Standard|R.");
		break;

	case 1:
		Patch(dwGameDll + 0x74C9F1, "\x68\xFF\x00\x00\x00", 5);
		Patch(dwGameDll + 0x3564B8, "\x66\x21\xC0", 3);
		TextPrint("|CFFFCD211Xenon|R: Fog of War has changed to |CFF00FF00Shared|R.");
		break;

	case 2:
		Patch(dwGameDll + 0x74C9F1, "\x8B\x14\x24\x90\x52", 5);
		Patch(dwGameDll + 0x3564B8, "\x66\x09\xD0", 3);
		TextPrint("|CFFFCD211Xenon|R: Fog of War has changed to |CFF00FF00None|R.");
		break;
	}
}