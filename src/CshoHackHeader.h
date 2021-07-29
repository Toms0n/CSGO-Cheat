#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "Vec3Header.h"

/*
* Traverse the process list to get the handle of the given process name.
*
* [proc_name] => the name of the process of which the handle is required
*
* [RETURNS] => the handle of the given process name
*/
DWORD AttachProcess(const wchar_t* proc_name);

/*
* Traverse the module list to get the base address of the given module name.
*
* [hProc] => the handle of the processes of the game
* [modName] => the module name to get the base address of
*
* [RETURNS] => pointer to the base address of the module
*/
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

/*
* ReadProcessMemory
*/
template<typename T>
T RPM(HANDLE hProc, SIZE_T address);

/*
* Reads the team id of the given player from memory of the process
*/
int GetTeamOfPlayer(HANDLE hProc, uintptr_t player);

/*
* Gets the address pointing to the local player (which is the player that you are playing)
*/
uintptr_t GetLocalPlayerAddr(HANDLE hProc, uintptr_t modBaseAddr);

/*
* Gets the current health from the player address from whom we want to know the HP of
*/
int GetPlayerHP(HANDLE hProc, uintptr_t playerAddr);

/*
* Gets the player current location (as 3d vector) in the game world
*/
Vec3 GetPlayerLocation(HANDLE hProc, uintptr_t playerAddr);

/*
* Checks whether the player that we are reading from is a real player and not something else in memory/game.
* If player is real then TRUE is returned, otherwise FALSE.
*/
bool DormantCheck(HANDLE hProc, uintptr_t playerAddr);

/*
* Fetch the given player head bone from memory
*/
Vec3 GetHeadLoc(HANDLE hProc, uintptr_t playerAddr);