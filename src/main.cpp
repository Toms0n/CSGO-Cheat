#include "CsgoCheats.h"
#include "Offsets.h"
#include <iostream>
#include <thread>
//#define NDEBUG // uncomment to disable assert()

static bool ENABLE_AIMBOT = true;
static bool ENABLE_GLOW = true;
static bool ENABLE_RADAR = false;

void Aimbot(std::shared_ptr<CsgoCheats> cc)
{
	if (ENABLE_AIMBOT)
	{
		while (!GetAsyncKeyState(VK_NUMPAD1))
		{
			cc->AimbotCheat(BoneList::BONE_HEAD);
			Sleep(1);
		}
	}
}

void GlowESP(std::shared_ptr<CsgoCheats> cc)
{
	if (ENABLE_GLOW)
	{
		while (!GetAsyncKeyState(VK_NUMPAD2))
		{
			cc->GlowWallhackCheat();
			Sleep(5);
		}
	}
}

void Radar(std::shared_ptr<CsgoCheats> cc)
{
	if (ENABLE_RADAR)
	{
		while (!GetAsyncKeyState(VK_NUMPAD3))
		{
			cc->RadarCheat();
			Sleep(10);
		}
	}
}

int main()
{
	// Initing and checking initialization of instances before starting the cheat
	std::shared_ptr<ProcessHandler> ph = std::make_shared<ProcessHandler>();
	if (ph->Init())
	{
		std::cout << "Successfully initialized ProcessHandler" << std::endl;
	}
	else
	{
		std::cout << "Failed to initialize ProcessHandler. Terminating..." << std::endl;
		return -1;
	}

	std::shared_ptr<WinScreenHandler> wsh = std::make_shared<WinScreenHandler>();
	if (wsh->Init())
	{
		std::cout << "Successfully initialized WinScreenHandler" << std::endl;
	}
	else
	{
		std::cout << "Failed to initialize WinScreenHandler. Terminating..." << std::endl;
		return -1;
	}

	std::shared_ptr<MemoryManager> mm = std::make_shared<MemoryManager>(ph);
	std::shared_ptr<CMath> cm = std::make_shared<CMath>();
	std::shared_ptr<CsgoCheats> c = std::make_shared<CsgoCheats>(
		ph,
		mm,
		wsh,
		cm
	);

	// Init and start threads for the cheats
	std::thread aimbot(Aimbot, c);
	std::thread glow(GlowESP, c);
	std::thread radar(Radar, c);
	
	// Wait for each thread to terminate by joining threads
	aimbot.join();
	glow.join();
	radar.join();
}