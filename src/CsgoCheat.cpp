#include "Offsets.h"
#include "CsgoCheatH.h"


CsgoAimbot::CsgoAimbot()
	: 
	m_Ph(std::make_shared<ProcessHandler>()),
	m_Mm(std::make_unique<MemoryManager>(m_Ph)),
	m_Wsh(std::make_unique<WinScreenHandler>()),
	crosshairX(m_Wsh->GetScreenWidth() / 2),
	crosshairY(m_Wsh->GetScreenHeight() / 2)
{
}

CsgoAimbot::~CsgoAimbot()
{
}

INT CsgoAimbot::GetTeamOfPlayer(UINT playerAddr)
{
	return m_Mm->RPM<INT>(playerAddr + m_iTeamNum);
}

UINT CsgoAimbot::GetLocalPlayerAddr()
{
	return m_Mm->RPM<UINT>(m_Ph->GetClientBase() + dwLocalPlayer);
}

UINT CsgoAimbot::GetPlayerAddr(UINT playerIndex)
{
	return m_Mm->RPM<UINT>(m_Ph->GetClientBase() + dwEntityList + (playerIndex * PLAYERS_INDEX_SEPERATION));
}

INT CsgoAimbot::GetPlayerHP(UINT playerAddr)
{
	return m_Mm->RPM<INT>(playerAddr + m_iHealth);
}

Vector3 CsgoAimbot::GetPlayerLocation(UINT playerAddr)
{
	return m_Mm->RPM<Vector3>(playerAddr + m_vecOrigin);
}

BOOL CsgoAimbot::DormantCheck(UINT playerAddr)
{
	return m_Mm->RPM<BOOL>(playerAddr + m_bDormant);
}

// TODO:
//Vector3 CsgoAimbot::GetBoneLoc(UINT playerAddr, uint32_t boneId)
//{
//	UINT baseBoneMatAddr = m_Mm->RPM<UINT>(playerAddr + m_dwBoneMatrix);
//	matrix boneMat = 
//		m_Mm->RPM<Math::boneMatrix>(baseBoneMatAddr + (sizeof(Math::boneMatrix) * boneId));
//	return Vector3(boneMat.x, boneMat.y, boneMat.z);
//}

// TODO:
//UINT CsgoAimbot::FindClosestEnemy(uint32_t boneId)
//{
//	FLOAT Finish;
//	INT ClosestEntity = 1;
//	Vector3 Calc = { 0, 0, 0 };
//	FLOAT Closest = FLT_MAX;
//	INT localTeam = GetTeamOfPlayer(GetLocalPlayerAddr());
//
//	for (UINT i = 1; i < 32; ++i) //Loops through all the entitys in the index 1-32.
//	{
//		UINT Entity = GetPlayerAddr(i);
//		INT EnmTeam = GetTeamOfPlayer(Entity); if (EnmTeam == localTeam) continue;
//		INT EnmHealth = GetPlayerHP(Entity); if (EnmHealth < 1 || EnmHealth > 100) continue;
//		BOOL Dormant = DormantCheck(Entity); if (Dormant) continue;
//
//		const Math::viewMatrix vm = m_Mm.RPM<Math::viewMatrix>(m_Ph.GetModBaseAddr() + dwViewMatrix);
//
//		Math::Vec3 headBone = Math::WorldToScreen(GetBoneLoc(Entity, boneId), vm);
//		Finish = Math::distance(headBone.x, headBone.y, this->crosshairX, this->crosshairY);
//		if (Finish < Closest)
//		{
//			Closest = Finish;
//			ClosestEntity = i;
//		}
//	}
//
//	return ClosestEntity;
//}







