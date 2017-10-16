#include "Warcraft.h"

bool bWoodCutter = false;

void WoodCutter()
{
	if (!bWoodCutter)
	{
		Patch(dwGameDll + 0x3A1505, "\x74", 1);

		TextPrint("|CFFFCD211Xenon|R: WoodCutter turned |CFF00FF00On|R.");

		bWoodCutter = true;
	}
	else
	{
		Patch(dwGameDll + 0x3A1505, "\x75", 1);

		TextPrint("|CFFFCD211Xenon|R: WoodCutter turned |CFFFF0000Off|R.");

		bWoodCutter = false;
	}
}