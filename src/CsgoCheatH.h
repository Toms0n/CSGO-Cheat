#pragma once

#include <iostream>
#include <windows.h>
#include <tlHelp32.h>
#include "MemoryManagerH.h"
#include "WinScreenHandlerH.h"
#include "ProcessHandlerH.h"
#include "Utils/Maths.h"
#include "Utils/Utils.h"

class CsgoAimbot
{
private:
	std::shared_ptr < ProcessHandler > m_Ph;
	std::unique_ptr < MemoryManager > m_Mm;
	std::unique_ptr < WinScreenHandler > m_Wsh;
	INT crosshairX;
	INT crosshairY;

public:
	CsgoAimbot();
	~CsgoAimbot();

	/*
	* Reads the team id of the given player from memory of the process
	*/
	INT GetTeamOfPlayer(UINT playerAddr);

	/*
	* Gets the address pointing to the local player (which is the player that you are playing)
	*/
	UINT GetLocalPlayerAddr();

	/*
	* Get the address of the player using its index
	*/
	UINT GetPlayerAddr(UINT playerIndex);

	/*
	* Gets the current health from the player address from whom we want to know the HP of
	*/
	INT GetPlayerHP(UINT playerAddr);

	/*
	* Gets the player current location (as 3d vector) in the game world
	*/
	Vector3 GetPlayerLocation(UINT playerAddr);

	/*
	* Checks whether the player that we are reading from is a real player and not something else in memory/game.
	* If player is NOT real then TRUE is returned, otherwise FALSE.
	*/
	BOOL DormantCheck(UINT playerAddr);

	/*
	* // TODO:
	* Fetch the given player head bone from memory
	*/
	//Vector3 GetBoneLoc(UINT playerAddr, uint32_t boneId);

	/*
	* // TODO:
	* Find the closest enemy to us by calculating distances from us to each other player and retrieve
	* the closest player that is an enemy, has health and is real. Retrun the player addr of the closest enemy.
	*/
	//UINT FindClosestEnemy(uint32_t boneId);
};
