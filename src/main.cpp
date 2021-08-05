#include "CsgoCheats.h"
#include "Offsets.h"

//#define NDEBUG // uncomment to disable assert()

//DWORD closestEnemyIdx; //Used in a thread to save CPU usage.

int main()
{
	CsgoCheats c;
	while (!GetAsyncKeyState(VK_END))
	{
		c.AimbotCheat(BoneList::BONE_HEAD);
		Sleep(1);
	}
}