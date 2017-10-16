#pragma once

class CUnit;
class CGameWar3;
class CAction;

void SafeClickInit(bool bIsInit);
void SendAction_interception();
bool __stdcall SendAction_Hook(CAction *lpAction);