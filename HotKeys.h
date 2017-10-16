#pragma once

#define VK_MapHack      VK_F5
#define VK_FogOfWar     VK_F6
// #define VK_DelayReducer VK_F7
#define VK_WoodCutter   VK_F7
#define VK_SafeClick    VK_F8
#define VK_ZoomIn       VK_ADD
#define VK_ZoomOut      VK_SUBTRACT
#define VK_Default      VK_MULTIPLY
#define VK_Scoreboard   VK_TAB
#define VK_ClearScreen  VK_BACK

void WINAPI HotKeys();
bool HotKeyPressed(int iKey);