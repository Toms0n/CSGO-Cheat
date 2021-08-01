#include "CsgoCheatHeader.h"
#include "Offsets.h"

uintptr_t closestEnemyIdx; //Used in a thread to save CPU usage.

// this is used only to pass multiple arguments to the CreateThread() function
struct ThreadArgs
{
	HANDLE hProc;
	uintptr_t modBaseAddress;
	uint32_t boneId;
};

void FindClosestEnemyThread(ThreadArgs threadArgs)
{
	while (1)
	{
		closestEnemyIdx = FindClosestEnemy(threadArgs.hProc, threadArgs.modBaseAddress, threadArgs.boneId);
	}
}

void DrawLine(float StartX, float StartY, float EndX, float EndY, HDC hdc)
{ //This function is optional for debugging.
	int a, b = 0;
	HPEN hOPen;
	HPEN hNPen = CreatePen(PS_SOLID, 2, 0x0000FF /*red*/);
	hOPen = (HPEN)SelectObject(hdc, hNPen);
	MoveToEx(hdc, StartX, StartY, NULL); //start of line
	a = LineTo(hdc, EndX, EndY); //end of line
	DeleteObject(SelectObject(hdc, hOPen));
}

template<typename T>
T RPM(HANDLE hProc, SIZE_T address)
{
	T buffer;
	ReadProcessMemory(hProc, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

int main()
{
	const auto BONE_USED = HEAD_BONE_ID;

	const DWORD PID = AttachProcess(L"csgo.exe");
	const uintptr_t modBaseAddr = GetModuleBaseAddress(PID, L"client.dll");

	if (PID == 0 || modBaseAddr == 0)
	{
		return -1;
	}

    HWND hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	HDC hdc = GetDC(hwnd);

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);
	ThreadArgs* TA = new ThreadArgs{ hProc, modBaseAddr, BONE_USED };

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)FindClosestEnemyThread, (LPVOID)TA, NULL, NULL);

	while (!GetAsyncKeyState(VK_END)) //press the "end" key to end the hack
	{ 
		const viewMatrix vm = RPM<viewMatrix>(hProc, modBaseAddr + dwViewMatrix);

		Vec3 boneLoc = GetBoneLoc(hProc, GetPlayerAddr(hProc, modBaseAddr, closestEnemyIdx), BONE_USED);
		Vec3 closestw2shead = WorldToScreen(boneLoc, vm);

		DrawLine(CROSSHAIR_X, CROSSHAIR_Y, closestw2shead.x, closestw2shead.y, hdc); //optinal for debugging

		if (GetAsyncKeyState(VK_MENU /*alt key*/) && closestw2shead.z >= 0.001f /*onscreen check*/)
			SetCursorPos(closestw2shead.x, closestw2shead.y); //turn off "raw input" in CSGO settings
	}

	delete TA;
}