#pragma once

void HideDll(HMODULE hModule);

void Patch(DWORD dwBaseAddress, char *szData, int iSize);

void PlantDetourCall(BYTE *bSource, BYTE *bDestination, int iLength);
void PlantDetourJump(BYTE *bSource, BYTE *bDestination, int iLength);

void SettingInitialize();
void SettingSet(char *szKey, char *szValue);
bool SettingGet(char *szKey);
bool FileExists(char *szFile);