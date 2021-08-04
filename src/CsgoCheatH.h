#pragma once

#include <iostream>
#include <windows.h>
#include <tlHelp32.h>
#include "MemoryManagerH.h"
#include "WinScreenHandlerH.h"
#include "ProcessHandlerH.h"
#include "Utils/Maths.h"
#include "Utils/Enums.h"
#include "Utils/Utils.h"

class CsgoAimbot
{
private:
	std::shared_ptr<ProcessHandler> m_Ph;
	std::unique_ptr<MemoryManager> m_Mm;
	std::unique_ptr<WinScreenHandler> m_Wsh;
	std::unique_ptr<CMath> m_Cmath;
	INT crosshairX;
	INT crosshairY;

public:
	CsgoAimbot();
	~CsgoAimbot();

	/*
	* Reads the team id of the given player from memory of the process
	*/
	Teams GetTeamOfPlayer(UINT playerAddr);

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
	* If player is NOT real then 1 (TRUE) is returned, otherwise 0 (FALSE).
	*/
	INT DormantCheck(UINT playerAddr);

	/*
	* Retrieves the 4x4 view matrix of the local player from memory
	*/
	viewMatrix GetViewMatrix();

	/*
	* Returns the bone matrix base address
	*/
	UINT GetBoneMatrixBaseAddr();

	/*
	* Fetch the given player head bone vector from memory
	*/
	Vector3 GetPlayerBoneLocation(UINT playerAddr, uint32_t boneId);

	/*
	* Transform an entities 3D position in-game to a 2D position on your screen
	* e.g. to render something on them (Wallhacks/ESP)
	* For more info about how W2S works:
	* - https://guidedhacking.com/threads/so-what-is-a-viewmatrix-anyway-and-how-does-a-w2s-work.10964/?__cf_chl_jschl_tk__=pmd_0dc52b4b4437ca3251053896bca209a151e75bcd-1628027647-0-gqNtZGzNAmKjcnBszQiO
	*/
	bool WorldToScreen(const Vector3& origin, Vector2& screen);

	/*
	* Find the closest enemy to us by calculating distances from us to each other player and retrieve
	* the closest player that is an enemy, has health and is real. Retrun the player addr of the closest enemy.
	*/
	UINT FindClosestEnemy(uint32_t boneId);

	INT GetCrosshairX();
	INT GetCrosshairY();
};
