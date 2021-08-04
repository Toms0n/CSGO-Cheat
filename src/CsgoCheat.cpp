#include "Offsets.h"
#include "CsgoCheatH.h"


CsgoAimbot::CsgoAimbot()
	: 
	m_Ph(std::make_shared<ProcessHandler>()),
	m_Mm(std::make_unique<MemoryManager>(m_Ph)),
	m_Wsh(std::make_unique<WinScreenHandler>()),
	m_Cmath(std::make_unique<CMath>()),
	crosshairX(m_Wsh->GetScreenWidth() / 2),
	crosshairY(m_Wsh->GetScreenHeight() / 2)
{
}

CsgoAimbot::~CsgoAimbot()
{
}

Teams CsgoAimbot::GetTeamOfPlayer(UINT playerAddr)
{
	return m_Mm->RPM<Teams>(playerAddr + netvars::m_iTeamNum);
}

UINT CsgoAimbot::GetLocalPlayerAddr()
{
	return m_Mm->RPM<UINT>(m_Ph->GetClientBase() + signatures::dwLocalPlayer);
}

UINT CsgoAimbot::GetPlayerAddr(UINT playerIndex)
{
	return m_Mm->RPM<UINT>(m_Ph->GetClientBase() + signatures::dwEntityList + (playerIndex * PLAYERS_INDEX_SEPERATION));
}

INT CsgoAimbot::GetPlayerHP(UINT playerAddr)
{
	return m_Mm->RPM<INT>(playerAddr + netvars::m_iHealth);
}

Vector3 CsgoAimbot::GetPlayerLocation(UINT playerAddr)
{
	return m_Mm->RPM<Vector3>(playerAddr + netvars::m_vecOrigin);
}

INT CsgoAimbot::DormantCheck(UINT playerAddr)
{
	return m_Mm->RPM<INT>(playerAddr + signatures::m_bDormant);
}

viewMatrix CsgoAimbot::GetViewMatrix()
{
	return m_Mm->RPM<viewMatrix>(m_Ph->GetClientBase() + signatures::dwViewMatrix);
}

UINT CsgoAimbot::GetBoneMatrixBaseAddr()
{
	return m_Mm->RPM<UINT>(m_Ph->GetClientBase() + netvars::m_dwBoneMatrix);
}

Vector3 CsgoAimbot::GetPlayerBoneLocation(UINT playerAddr, uint32_t boneId)
{
	UINT baseBoneMatAddr = GetBoneMatrixBaseAddr();
	const boneMatrix boneMat =
		m_Mm->RPM<boneMatrix>(baseBoneMatAddr + (sizeof(boneMatrix) * boneId));
	return Vector3(boneMat.x, boneMat.y, boneMat.z);
}

bool CsgoAimbot::WorldToScreen(const Vector3& worldPosVec, Vector2& screen)
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

	// get the screen width and height
	const auto screenW = m_Wsh->GetScreenWidth();
	const auto screenH = m_Wsh->GetScreenHeight();

	// final, real screen positions
	// TODO: this can be optimized by reducing amount of calculations
	screen.x = (screenW / 2 * screen.x) + (screen.x + screenW / 2);
	screen.y = -(screenH / 2 * screen.y) + (screen.y + screenH / 2);

	return true;
}

UINT CsgoAimbot::FindClosestEnemy(uint32_t boneId)
{
	FLOAT finish;
	Vector3 calc;
	INT closestEntity = 1;
	FLOAT closest = FLT_MAX;

	UINT localPlayerAddr = GetLocalPlayerAddr();
	Teams localTeam = GetTeamOfPlayer(localPlayerAddr);

	for (UINT i = 1; i < 32; ++i) //Loops through all the entitys in the index 1-32.
	{
		UINT entity = GetPlayerAddr(i);
		INT EnmTeam = GetTeamOfPlayer(entity); if (EnmTeam == localTeam) continue;
		INT EnmHealth = GetPlayerHP(entity); if (EnmHealth < 1 || EnmHealth > 100) continue;
		BOOL Dormant = DormantCheck(entity); if (Dormant) continue;

		const Vector3 playerBoneWorldPos = GetPlayerBoneLocation(entity, boneId);
		Vector2 screenPos;

		WorldToScreen(playerBoneWorldPos, screenPos);

		finish = (float)FastSQRT(pow(screenPos.x - this->crosshairX, 2) + pow(screenPos.y - this->crosshairY, 2));

		if (finish < closest)
		{
			closest = finish;
			closestEntity = i;
		}
	}

	return closestEntity;
}

INT CsgoAimbot::GetCrosshairX() { return crosshairX; }
INT CsgoAimbot::GetCrosshairY() { return crosshairY; }





