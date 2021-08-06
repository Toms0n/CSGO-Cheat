#include "Offsets.h"
#include "CsgoCheats.h"


CsgoCheats::CsgoCheats(
	const std::shared_ptr<ProcessHandler> _Ph,
	const std::shared_ptr<MemoryManager> _Mm,
	const std::shared_ptr<WinScreenHandler> _Wsh,
	const std::shared_ptr<CMath> _Cm
)
	:
	m_Ph(_Ph),
	m_Mm(_Mm),
	m_Wsh(_Wsh),
	m_Cmath(_Cm),
	clientStateAddr(
		m_Mm->RPM<DWORD>(m_Ph->GetEngineBase() + signatures::dwClientState)
	),
	glowObjectManagerAddr(
		m_Mm->RPM<DWORD>(m_Ph->GetClientBase() + signatures::dwGlowObjectManager)
	),
	crosshairX(m_Wsh->GetScreenWidth() / 2),
	crosshairY(m_Wsh->GetScreenHeight() / 2)
{
}

CsgoCheats::~CsgoCheats()
{
#ifdef _DEBUG
	std::cout << "~CsgoCheats() Called!" << std::endl;
#endif
}

inline INT CsgoCheats::GetTeamOfPlayer(const DWORD playerAddr)
{
	return m_Mm->RPM<INT>(playerAddr + netvars::m_iTeamNum);
}

inline DWORD CsgoCheats::GetLocalPlayerAddr()
{
	return m_Mm->RPM<DWORD>(m_Ph->GetClientBase() + signatures::dwLocalPlayer);
}

inline DWORD CsgoCheats::GetPlayerAddr(const INT playerIndex)
{
	return m_Mm->RPM<DWORD>(m_Ph->GetClientBase() + signatures::dwEntityList + (playerIndex * PLAYERS_INDEX_SEPERATION));
}

inline INT CsgoCheats::GetPlayerHP(const DWORD playerAddr)
{
	return m_Mm->RPM<INT>(playerAddr + netvars::m_iHealth);
}

inline Vector3 CsgoCheats::GetPlayerLocation(const DWORD playerAddr)
{
	return m_Mm->RPM<Vector3>(playerAddr + netvars::m_vecOrigin);
}

inline INT CsgoCheats::GetPlayerGlowIndex(const DWORD playerAddr)
{
	return m_Mm->RPM<INT>(playerAddr + netvars::m_iGlowIndex);
}

inline GlowStruct CsgoCheats::GetPlayerGlow(const INT glowIdx)
{
	return m_Mm->RPM<GlowStruct>(
		glowObjectManagerAddr + 
		(glowIdx * GLOW_IDX_SEPERATION) +
		GLOW_VALUES_OFFSET
	);
}

inline bool CsgoCheats::SetPlayerGlow(const INT glowIdx)
{
	auto g = GetPlayerGlow(glowIdx);
	g.rbga.r = 1.f;
	g.rbga.a = 0.7f;
	g.renderOccluded = true;
	g.renderUnoccluded = false;

	return m_Mm->WPM<GlowStruct>(
		glowObjectManagerAddr + 
		(glowIdx * GLOW_IDX_SEPERATION) + 
		GLOW_VALUES_OFFSET
		, g
	);
}

inline bool CsgoCheats::DormantCheck(const DWORD playerAddr)
{
	return m_Mm->RPM<bool>(playerAddr + signatures::m_bDormant);
}

inline Vector3 CsgoCheats::GetLocalPlayerViewAngles()
{
	return m_Mm->RPM<Vector3>(clientStateAddr + signatures::dwClientState_ViewAngles);
}

inline bool CsgoCheats::SetLocalPlayerViewAngles(const Vector3& angles)
{
	return m_Mm->WPM<Vector3>(clientStateAddr + signatures::dwClientState_ViewAngles, angles);
}

inline viewMatrix CsgoCheats::GetViewMatrix()
{
	return m_Mm->RPM<viewMatrix>(m_Ph->GetClientBase() + signatures::dwViewMatrix);
}

inline DWORD CsgoCheats::GetLocalPlayerBoneMatrixBaseAddr()
{
	return m_Mm->RPM<UINT>(m_Ph->GetClientBase() + netvars::m_dwBoneMatrix);
}

inline DWORD CsgoCheats::GetPlayerBoneMatrixBaseAddr(const DWORD playerAddr)
{
	return m_Mm->RPM<UINT>(playerAddr + netvars::m_dwBoneMatrix);
}

inline Vector3 CsgoCheats::GetPlayerBoneLocation(const DWORD playerAddr, const uint32_t boneId)
{
	const UINT baseBoneMatAddr = GetPlayerBoneMatrixBaseAddr(playerAddr);
	const boneMatrix boneMat =
		m_Mm->RPM<boneMatrix>(baseBoneMatAddr + (sizeof(boneMatrix) * boneId));
	return Vector3(boneMat.x, boneMat.y, boneMat.z);
}

inline bool CsgoCheats::WorldToScreen(const Vector3& worldPosVec, Vector2& screen)
{
	const viewMatrix& w2sMatrix = GetViewMatrix();

	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	screen.x = w2sMatrix.flMatrix[0][0] * worldPosVec.x +
		w2sMatrix.flMatrix[0][1] * worldPosVec.y +
		w2sMatrix.flMatrix[0][2] * worldPosVec.z +
		w2sMatrix.flMatrix[0][3];
	screen.y = w2sMatrix.flMatrix[1][0] * worldPosVec.x +
		w2sMatrix.flMatrix[1][1] * worldPosVec.y +
		w2sMatrix.flMatrix[1][2] * worldPosVec.z +
		w2sMatrix.flMatrix[1][3];

	// Third vector in the matrix (called W) helps us determine whether we even need to draw
	float W = w2sMatrix.flMatrix[3][0] * worldPosVec.x +
		w2sMatrix.flMatrix[3][1] * worldPosVec.y +
		w2sMatrix.flMatrix[3][2] * worldPosVec.z +
		w2sMatrix.flMatrix[3][3];

	// if W is 0 then it is not on our screen (but behind us, thus don't bother drawing). 
	// Else it is on the screen (in front of us where we can see it).
	if (W < 0.1f)
		return false;

	// Scale the screen vector to your screen dimensions
	// This is called converting from Clip-Space to Window-Space (called NDC = Normalized Device Coordinates)
	// using Perspective divide, simply divide screen values by W.
	screen.x /= W;
	screen.y /= W;

	// final, real screen positions
	screen.x = (crosshairX * screen.x) + (screen.x + crosshairX);
	screen.y = -(crosshairY * screen.y) + (screen.y + crosshairY);

	return true;
}

inline bool CsgoCheats::GetEnemySpotted(const DWORD playerAddr)
{
	return m_Mm->RPM<bool>(playerAddr + netvars::m_bSpotted);
}

inline void CsgoCheats::SetEnemySpotted(const DWORD playerAddr, const bool isSpotted)
{
	m_Mm->WPM(playerAddr + netvars::m_bSpotted, isSpotted);
}

inline INT CsgoCheats::GetClientState()
{
	return m_Mm->RPM<INT>(clientStateAddr + signatures::dwClientState_State);
}

inline bool CsgoCheats::IsEntityImmune(const DWORD playerAddr)
{
	return m_Mm->RPM<bool>(playerAddr + netvars::m_bGunGameImmunity);
}

inline bool CsgoCheats::isAlive(const DWORD playerAddr)
{
	const INT entHp = GetPlayerHP(playerAddr);
	if (entHp > 0 && entHp <= 100)
		return true;
	return false;
}

inline bool CsgoCheats::IsEntityValid(const DWORD playerAddr)
{
	// check if player has a valid team
	const INT entTeam = GetTeamOfPlayer(playerAddr);
	if (entTeam != Teams::T && entTeam != Teams::CT) return false;

	// check if entity is alive and not dead
	const bool isEntAlive = isAlive(playerAddr);
	if (!isEntAlive) return false;

	// check if entity is dormant
	const bool entDormant = DormantCheck(playerAddr); 
	if (entDormant) return false;

	// check if player is invisible or in immune mode (e.g. 2 seconds after respawning)
	const bool isImmune = IsEntityImmune(playerAddr);
	if (isImmune) return false;

	return true;
}

inline DWORD CsgoCheats::FindClosestEnemyToCrosshair(const uint32_t boneId)
{
	DWORD closestEnemyAddr = NULL;
	FLOAT closestEntityDist = FLT_MAX;

	const DWORD localPlayerAddr = GetLocalPlayerAddr();
	const INT localTeam = GetTeamOfPlayer(localPlayerAddr);

	for (unsigned int i = 1; i < 64; ++i) //Loops through all the player entity indexes.
	{
		const DWORD entity = GetPlayerAddr(i);

		const INT EnmTeam = GetTeamOfPlayer(entity); if (EnmTeam == localTeam) continue;
		const bool isEntValid = IsEntityValid(entity); if (!isEntValid) continue;

		const Vector3 playerBoneWorldPos = GetPlayerBoneLocation(entity, boneId);
		Vector2 screenPos;

		WorldToScreen(playerBoneWorldPos, screenPos);

		const FLOAT currEntityDist = 
			(float)FastSQRT(pow(screenPos.x - crosshairX, 2) + pow(screenPos.y - crosshairY, 2));

		if (currEntityDist < closestEntityDist)
		{
			closestEntityDist = currEntityDist;
			closestEnemyAddr = entity;
		}
	}

	return closestEnemyAddr;
}

#ifdef _DEBUG
void CsgoCheats::FOR_DEBUGGING(DWORD closestEnemy, uint32_t boneId)
{
	const Vector3 playerBoneWorldPos = GetPlayerBoneLocation(closestEnemy, boneId);
	Vector2 closestPlayerScreenPos;

	if (WorldToScreen(playerBoneWorldPos, closestPlayerScreenPos))
	{
		m_Wsh->DrawLine(crosshairX, crosshairY, closestPlayerScreenPos.x, closestPlayerScreenPos.y); //for debugging
	}
}
#endif

inline Vector3 CsgoCheats::GetLocalPlayerPunchAngles()
{
	return m_Mm->RPM<Vector3>(GetLocalPlayerAddr() + netvars::m_aimPunchAngle);
}

inline Vector3 CsgoCheats::GetPlayerEyePos(const DWORD playerAddr, const Vector3& playerOrigin)
{
	return playerOrigin + m_Mm->RPM<Vector3>(playerAddr + netvars::m_vecViewOffset);
}

void CsgoCheats::RadarCheat()
{
	const auto localPlayerAddr = GetLocalPlayerAddr();
	const auto localPlayerTeam = GetTeamOfPlayer(localPlayerAddr);

	for (unsigned int i = 1; i < 64; i++)
	{
		const auto playerAddr = GetPlayerAddr(i);

		// only set enemies as spotted
		if (GetTeamOfPlayer(playerAddr) != localPlayerTeam &&
			IsEntityValid(playerAddr))
		{
			SetEnemySpotted(playerAddr, 1);
		}
	}
}

void CsgoCheats::AimbotCheat(const uint32_t boneId)
{
	// TODO: finding closest enemy here in inf. loop in single thread is not efficient
	// make new thread with only task to find closest enemy and start it first here
	// or make new thread that executes the AimbotCheat function in an inf loop (optional).
	const DWORD closestEnemyAddr = FindClosestEnemyToCrosshair(boneId);
	
	if (closestEnemyAddr != NULL)
	{
#ifdef _DEBUG
		FOR_DEBUGGING(closestEnemyAddr, boneId);
#endif
		const DWORD localPlayerAddr = GetLocalPlayerAddr();

		/* ENABLE AIMBOT WHEN GIVEN KEY IS PRESSED */
		if (GetAsyncKeyState(VK_LBUTTON) 
			//&& GetEnemySpotted(closestEnemyAddr)
		)
		{
			const auto localPlayerPos = GetPlayerLocation(localPlayerAddr);
			const auto enemyPlayerPos = GetPlayerLocation(closestEnemyAddr);

			const auto localPlayerEyePos = GetPlayerEyePos(localPlayerAddr, localPlayerPos);
			const auto enemyHeadPos = GetPlayerBoneLocation(closestEnemyAddr, boneId);

			const Vector3 currAimAngles = GetLocalPlayerViewAngles();
			Vector3 aimAngles = m_Cmath->CalcAngle(localPlayerEyePos, enemyHeadPos);
			//Vector3 aimAngles = m_Cmath->CalcAngle(localPlayerPos, enemyPlayerPos);

			// remove recoil
			aimAngles -= GetLocalPlayerPunchAngles() * 2.f;

			// 1) Get delta of current aim angle to destination
			// 2) Clamp/normalize delta vector to not be detected by VAC 
			// and avoid aim flicks to unexpected places in the world
			// 3) apply linear smoothing to the clamped angle to not be obvious with aim
			// so if the smooth is high, then change of angle to destination angle is less immidiate
			// and the lower the smooth, the faster it is going from curr aim angles to desination angles
			// e.g. smooth=1, then there is no smooth and angle is immidiately changed to enemy bone pos
			m_Cmath->SmoothAngle(currAimAngles, aimAngles, 1);

			// set destination angles
			SetLocalPlayerViewAngles(aimAngles);
		}
	}
}

void CsgoCheats::GlowWallhackCheat()
{
	const auto localPlayerAddr = GetLocalPlayerAddr();
	const auto localPlayerTeam = GetTeamOfPlayer(localPlayerAddr);

	for (unsigned int i = 1; i < 64; i++)
	{
		const auto playerAddr = GetPlayerAddr(i);

		if (playerAddr != NULL)
		{
			if (!IsEntityValid(playerAddr)) continue;
			if (GetTeamOfPlayer(playerAddr) == localPlayerTeam) continue;

			const auto enemyGlowIdx = GetPlayerGlowIndex(playerAddr);
			SetPlayerGlow(enemyGlowIdx);
		}
	}
}





