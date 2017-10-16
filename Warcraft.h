#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

const HWND  hWnd      = FindWindow("Warcraft III", NULL);
const DWORD dwGameDll = (DWORD)GetModuleHandle("Game.dll");

#include "Functions.h"
#include "HotKeys.h"

#include "Jass Natives.h"

#include "States.h"
#include "Camera Distance Hack.h"
#include "Color Invisibles.h"
#include "Damage Notifier.h"
#include "Delay Reducer.h"
#include "Dream UI.h"
#include "Game Start Notifier.h"
#include "Gray HP Under Fog.h"
#include "Instant Game Start.h"
#include "Mana Bar.h"
#include "Map Hack.h"
#include "Roshan Notifier.h"
#include "Rune Notifier.h"
#include "SafeClick.h"
#include "Scoreboard Shortcut Key.h"
#include "Warcraft Functions.h"
#include "WoodCutter.h"