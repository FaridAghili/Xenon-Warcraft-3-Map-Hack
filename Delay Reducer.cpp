#include "Warcraft.h"

bool bDelayReducer = false;

void DelayReducer()
{
	if (!bDelayReducer)
	{
		Patch(dwGameDll + 0x551768, "\xD3\x90\x90\x90\x90", 5);
		Patch(dwGameDll + 0x55177A, "\x01", 1);

		TextPrint("|CFFFCD211Xenon|R: Delay Reducer turned |CFF00FF00On|R.");

		bDelayReducer = true;
	}
	else
	{
		Patch(dwGameDll + 0x551768, "\x96\x58\x22\x00\x00", 5);
		Patch(dwGameDll + 0x55177A, "\x03", 1);

		TextPrint("|CFFFCD211Xenon|R: Delay Reducer turned |CFFFF0000Off|R.");

		bDelayReducer = false;
	}
}