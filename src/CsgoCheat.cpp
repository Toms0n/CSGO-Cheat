#include "Offsets.h"
#include "CsgoCheatHeader.h"
#include "MemoryManagerH.h"
#include "WinScreenHandlerH.h"
#include "ProcessHandlerH.h"
#include "MathH.h"

CsgoAimbot::CsgoAimbot()
	: 
	m_Mm(MemoryManager()),
	m_Wsh(WinScreenHandler()),
	m_Ph(ProcessHandler()),
	crosshairX(m_Wsh.GetScreenWidth() / 2),
	crosshairY(m_Wsh.GetScreenHeight() / 2)
{
}

INT CsgoAimbot::GetTeamOfPlayer(UINT playerAddr)
{
	return m_Mm.RPM<INT>(playerAddr + m_iTeamNum);
}

UINT CsgoAimbot::GetLocalPlayerAddr()
{
	return m_Mm.RPM<UINT>(m_Ph.GetModBaseAddr() + dwLocalPlayer);
}

UINT CsgoAimbot::GetPlayerAddr(UINT playerIndex)
{
	return m_Mm.RPM<UINT>(m_Ph.GetModBaseAddr() + dwEntityList + (playerIndex * PLAYERS_INDEX_SEPERATION));
}

INT CsgoAimbot::GetPlayerHP(UINT playerAddr)
{
	return m_Mm.RPM<INT>(playerAddr + m_iHealth);
}

Math::Vec3 CsgoAimbot::GetPlayerLocation(UINT playerAddr)
{
	return m_Mm.RPM<Math::Vec3>(playerAddr + m_vecOrigin);
}

BOOL CsgoAimbot::DormantCheck(UINT playerAddr)
{
	return m_Mm.RPM<BOOL>(playerAddr + m_bDormant);
}

Math::Vec3 CsgoAimbot::GetBoneLoc(UINT playerAddr, uint32_t boneId)
{
	UINT baseBoneMatAddr = m_Mm.RPM<UINT>(playerAddr + m_dwBoneMatrix);
	Math::boneMatrix boneMat = 
		m_Mm.RPM<Math::boneMatrix>(baseBoneMatAddr + (sizeof(Math::boneMatrix) * boneId));
	return Math::Vec3(boneMat.x, boneMat.y, boneMat.z);
}

UINT CsgoAimbot::FindClosestEnemy(uint32_t boneId)
{
	FLOAT Finish;
	INT ClosestEntity = 1;
	Math::Vec3 Calc = { 0, 0, 0 };
	FLOAT Closest = FLT_MAX;
	INT localTeam = GetTeamOfPlayer(GetLocalPlayerAddr());

	for (UINT i = 1; i < 32; ++i) //Loops through all the entitys in the index 1-32.
	{
		UINT Entity = GetPlayerAddr(i);
		INT EnmTeam = GetTeamOfPlayer(Entity); if (EnmTeam == localTeam) continue;
		INT EnmHealth = GetPlayerHP(Entity); if (EnmHealth < 1 || EnmHealth > 100) continue;
		BOOL Dormant = DormantCheck(Entity); if (Dormant) continue;

		const Math::viewMatrix vm = m_Mm.RPM<Math::viewMatrix>(m_Ph.GetModBaseAddr() + dwViewMatrix);

		Math::Vec3 headBone = Math::WorldToScreen(GetBoneLoc(Entity, boneId), vm);
		Finish = Math::distance(headBone.x, headBone.y, this->crosshairX, this->crosshairY);
		if (Finish < Closest)
		{
			Closest = Finish;
			ClosestEntity = i;
		}
	}

	return ClosestEntity;
}







