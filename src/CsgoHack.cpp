#include "CshoHackHeader.h"
#include "Offsets.h"

//global vars
const uint32_t SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const uint32_t SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const uint32_t CROSSHAIR_X = SCREEN_WIDTH / 2;
const uint32_t CROSSHAIR_Y= SCREEN_HEIGHT / 2;

DWORD AttachProcess(const wchar_t* proc_name)
{
	DWORD PID = 0;

	// Take a snapshot of all processes in the system.
	auto hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (hProcSnap != INVALID_HANDLE_VALUE)
	{
		// processes structure object
		PROCESSENTRY32 procEnt;

		// Set the size of the structure before using it.
		procEnt.dwSize = sizeof(procEnt);

		// Now walk the snapshot of processes, and
		// display information about each process in turn
		while (Process32Next(hProcSnap, &procEnt))
		{
			if (!_wcsicmp(proc_name, procEnt.szExeFile))
			{
				std::cout << "Process found: " << procEnt.szExeFile << " PID: " << procEnt.th32ProcessID << std::endl;
				PID = procEnt.th32ProcessID;
				break;
			}
		}
	}
	else
	{
		std::cout << "Could not get snapshot of all running processes." << std::endl;
	}

	if (PID == 0)
	{
		std::cout << "Process " << proc_name << " could not be found in the process list" << std::endl;
	}

	CloseHandle(hProcSnap);
	return PID;
}


uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEnt;
		modEnt.dwSize = sizeof(modEnt);

		while (Module32Next(hSnap, &modEnt))
		{
			if (!_wcsicmp(modEnt.szModule, modName))
			{
				std::cout << "Module found: " << modName << std::endl;
				modBaseAddr = (uintptr_t)modEnt.modBaseAddr;
				break;
			}
		}
	}
	else
	{
		std::cout << "Could not get snapshot of modules." << std::endl;
	}

	if (modBaseAddr == 0)
	{
		std::cout << "Module " << modName << " could not be found in the modules list" << std::endl;
	}

	CloseHandle(hSnap);
	return modBaseAddr;
}

template<typename T>
T RPM(HANDLE hProc, SIZE_T address)
{
	T buffer;
	ReadProcessMemory(hProc, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

int GetTeamOfPlayer(HANDLE hProc, uintptr_t playerAddr)
{
	return RPM<int>(hProc, playerAddr + m_iTeamNum);
}

uintptr_t GetLocalPlayerAddr(HANDLE hProc, uintptr_t modBaseAddr)
{
	return RPM<uintptr_t>(hProc, modBaseAddr + dwLocalPlayer);
}

uintptr_t GetPlayerAddr(HANDLE hProc, uintptr_t modBaseAddr, uint32_t playerIndex)
{
	return RPM<uintptr_t>(hProc, modBaseAddr + dwEntityList + (playerIndex * PLAYERS_INDEX_SEPERATION) );
}

int GetPlayerHP(HANDLE hProc, uintptr_t playerAddr)
{
	return RPM<int>(hProc, playerAddr + m_iHealth);
}

Vec3 GetPlayerLocation(HANDLE hProc, uintptr_t playerAddr)
{
	return RPM<Vec3>(hProc, playerAddr + m_vecOrigin);
}

bool DormantCheck(HANDLE hProc, uintptr_t playerAddr)
{
	return RPM<int>(hProc, playerAddr + m_bDormant);
}

Vec3 GetHeadLoc(HANDLE hProc, uintptr_t playerAddr)
{

}