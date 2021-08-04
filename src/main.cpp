#include "CsgoCheatH.h"
#include "Offsets.h"

//#define NDEBUG // uncomment to disable assert()

uintptr_t closestEnemyIdx; //Used in a thread to save CPU usage.

//This function is optional for debugging.
void DrawLine(float StartX, float StartY, float EndX, float EndY, HDC hdc)
{ 
	int a, b = 0;
	HPEN hOPen;
	HPEN hNPen = CreatePen(PS_SOLID, 2, 0x0000FF /*red*/);
	hOPen = (HPEN)SelectObject(hdc, hNPen);
	MoveToEx(hdc, StartX, StartY, NULL); //start of line
	a = LineTo(hdc, EndX, EndY); //end of line
	DeleteObject(SelectObject(hdc, hOPen));
}

int main()
{
	HWND hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	HDC	hdc = GetDC(hwnd);
	CsgoAimbot c;
	INT headBone = BONE_HEAD;
	INT crosshairX = c.GetCrosshairX();
	INT crosshairY = c.GetCrosshairY();

	while (!GetAsyncKeyState(VK_END))
	{ //press the "end" key to end the hack
		closestEnemyIdx = c.FindClosestEnemy(headBone);

		const Vector3 playerBoneWorldPos = c.GetPlayerBoneLocation(closestEnemyIdx, headBone);
		Vector2 screenPos;

		if (c.WorldToScreen(playerBoneWorldPos, screenPos))
		{
			DrawLine(crosshairX, crosshairY, screenPos.x, screenPos.y, hdc); //optinal for debugging
			if (GetAsyncKeyState(VK_MENU /*alt key*/))
				SetCursorPos(screenPos.x, screenPos.y); //turn off "raw input" in CSGO settings
		}
	}

	//while (1)
	//{
	//	if (GetAsyncKeyState(VK_CAPITAL)) break;

	//	auto me = c.GetLocalPlayerAddr();
	//	auto isDormant = c.DormantCheck(me);
	//	auto myHp = c.GetPlayerHP(me);
	//	auto myTeam = c.GetTeamOfPlayer(me);
	//	auto myLoc = c.GetPlayerLocation(me);
	//	auto vm = c.GetViewMatrix();

	//	std::cout << "IsDormant " << isDormant << std::endl;
	//	std::cout << "My HP " << myHp << std::endl;
	//	std::cout << "My Team " << myTeam << std::endl;
	//	std::cout << "My Loc (" << myLoc.x << "," << myLoc.y << "," << myLoc.z << ")" << std::endl;

	//	/*for (unsigned int i = 0; i < 4; ++i)
	//	{
	//		std::cout << "[";
	//		for (unsigned int j = 0; j < 4; j++)
	//		{
	//			if (j == 3)
	//			{
	//				std::cout << vm.flMatrix[i][j];
	//			}
	//			else
	//			{
	//				std::cout << vm.flMatrix[i][j] << ", ";
	//			}
	//		}
	//		std::cout << "]" << std::endl;
	//	}*/

	//	// enumerate all the entities in the entity list
	//	/*for (unsigned int i = 0; i < 32; ++i)
	//	{
	//		auto entList = c.m_Mm->()
	//	}*/

	//	Sleep(5000);
	//}
}