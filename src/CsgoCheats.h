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

class CsgoCheats
{
private:
	std::shared_ptr<ProcessHandler> m_Ph;
	std::unique_ptr<MemoryManager> m_Mm;
	std::unique_ptr<WinScreenHandler> m_Wsh;
	std::unique_ptr<CMath> m_Cmath; // needed for aimbot
	DWORD clientState; // needed for view angels
	INT crosshairX;
	INT crosshairY;

	/*
	* Reads the team id of the given player from memory of the process
	*/
	INT GetTeamOfPlayer(DWORD playerAddr);

	/*
	* Gets the address pointing to the local player (which is the player that you are playing)
	*/
	DWORD GetLocalPlayerAddr();

	/*
	* Get the address of the player using its index
	*/
	DWORD GetPlayerAddr(INT playerIndex);

	/*
	* Get the eye position of the given player address and origin vector
	* of the player in the world
	*/
	Vector3 GetPlayerEyePos(DWORD playerAddr, const Vector3& playerOrigin);

	/*
	* Get the current punch/recoil angles of the localplayer
	*/
	Vector3 GetLocalPlayerPunchAngles();

	/*
	* Gets the current health from the player address from whom we want to know the HP of
	*/
	INT GetPlayerHP(DWORD playerAddr);

	/*
	* Gets the player current location (as 3d vector) in the game world
	*/
	Vector3 GetPlayerLocation(DWORD playerAddr);

	/*
	* Get the glow index of the given player with playerAddr
	*/
	INT GetPlayerGlowIndex(DWORD playerAddr);

	/*
	* Gets the glow manager object memory address
	*/
	DWORD GetGlowManagerAddr();

	/*
	* Checks whether the player that we are reading from is a real player and not something else in memory/game.
	* If player is NOT real then 1 (TRUE) is returned, otherwise 0 (FALSE).
	*/
	bool DormantCheck(DWORD playerAddr);

	/*
	* Get the current view angles of the localplayer
	*/
	Vector3 GetLocalPlayerViewAngles();

	/*
	* Set the current view angles of the localplayer to the given angles
	*/
	bool SetLocalPlayerViewAngles(const Vector3& angles);

	/*
	* Retrieves the 4x4 view matrix of the local player from memory
	*/
	viewMatrix GetViewMatrix();

	/*
	* Returns the bone matrix base address of local player
	*/
	DWORD GetLocalPlayerBoneMatrixBaseAddr();

	/*
	* Returns the bone matrix base address of entity player
	*/
	DWORD GetPlayerBoneMatrixBaseAddr(DWORD playerAddr);

	/*
	* Fetch the given player head bone vector from memory
	*/
	Vector3 GetPlayerBoneLocation(DWORD playerAddr, uint32_t boneId);

	/*
	* Transform an entities 3D position in-game to a 2D position on your screen
	* e.g. to render something on them (Wallhacks/ESP)
	* For more info about how W2S works:
	* - https://guidedhacking.com/threads/so-what-is-a-viewmatrix-anyway-and-how-does-a-w2s-work.10964/?__cf_chl_jschl_tk__=pmd_0dc52b4b4437ca3251053896bca209a151e75bcd-1628027647-0-gqNtZGzNAmKjcnBszQiO
	*/
	bool WorldToScreen(const Vector3& origin, Vector2& screen);

	/*
	* The state of the client (e.g. loading, connecting, in-game etc...)
	*/
	INT GetClientState();

	/*
	* Returns an INT. 1 if enemy is spotted, otherwise 0.
	*/
	bool GetEnemySpotted(DWORD playerAddr);

	/*
	* Sets enemies as spotted (used for radar hack)
	*/
	void SetEnemySpotted(DWORD playerAddr, bool isSpotted);

	/*
	* Checks whether the entity is a valid entity (and not e.g. dormant)
	*/
	bool IsEntityValid(DWORD playerAddr);

	/*
	* Checks if player is immune to damage
	*/
	bool IsEntityImmune(DWORD playerAddr);

	/*
	* Check if player is alive
	*/
	bool isAlive(DWORD playerAddr);

	/*
	* Find the closest enemy to us by calculating distances from us to each other player and retrieve
	* the closest player that is an enemy, has health and is real. Retrun the player addr of the closest enemy.
	*/
	DWORD FindClosestEnemyToCrosshair(uint32_t boneId);

	/*
	// TODO: delete this
	*/
	void FOR_DEBUGGING(DWORD closestEnemy, uint32_t boneId);

public:
	CsgoCheats();
	~CsgoCheats();

	/*
	* Enables radar hack (shows enemies in the map as red spots)
	*/
	void RadarCheat();

	/*
	* Enables aimbot. boneId is the bone to aim at e.g. HEAD_BONE.
	*/
	void AimbotCheat(uint32_t boneId);

	/*
	* TODO: Makes enemy entities glow through walls
	*/
	void GlowWallhackCheat();
};
