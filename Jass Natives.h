#pragma once

void JassNativesInit();

// FogEnable
typedef void (__cdecl *GAME_FogEnable) (bool flag);
// FogMaskEnable
typedef void (__cdecl *GAME_FogMaskEnable) (bool flag);

// PingMinimapEx
typedef void (__cdecl *GAME_PingMinimapEx)(float *x, float *y, float *duration, int red, int green, int blue, bool extraEffects);

// ClearTextMessages
typedef void (__cdecl *GAME_ClearTextMessages)(void);

// PauseGame
typedef void (__cdecl *GAME_PauseGame)(bool flag);

// GetLocalPlayer
typedef DWORD (__cdecl *GAME_GetLocalPlayer)(void);

// GetTriggerUnit
typedef DWORD (__cdecl *GAME_GetTriggerUnit)(void);

// IsUnitOwnedByPlayer
typedef bool (__cdecl *GAME_IsUnitOwnedByPlayer)(DWORD whichUnit, DWORD whichPlayer);

// CreateTextTag
typedef DWORD (__cdecl *GAME_CreateTextTag)(void);
// SetTextTagPosUnit
typedef void (__cdecl *GAME_SetTextTagPosUnit)(DWORD t, DWORD whichUnit, float *heightOffset);
// SetTextTagColor
typedef void (__cdecl *GAME_SetTextTagColor)(DWORD t, int red, int green, int blue, int alpha);
// SetTextTagVelocity
typedef void (__cdecl *GAME_SetTextTagVelocity)(DWORD t, float *xvel, float *yvel);
// SetTextTagVisibility
typedef void (__cdecl *GAME_SetTextTagVisibility)(DWORD t, bool flag);
// SetTextTagPermanent
typedef void (__cdecl *GAME_SetTextTagPermanent)(DWORD t, bool flag);
// SetTextTagLifespan
typedef void (__cdecl *GAME_SetTextTagLifespan)(DWORD t, float *lifespan);
// SetTextTagFadepoint
typedef void (__cdecl *GAME_SetTextTagFadepoint)(DWORD t, float *fadepoint);
// SetTextTagText
void SetTextTagText(int t, char *s, float *height);

char *GetUnitName(DWORD hUnit);
char *GetItemName(DWORD hItem);

void IntToRawCode(long int num, char *cToCopy);

bool IsItem(DWORD dwItemHandle, char *szItemName);