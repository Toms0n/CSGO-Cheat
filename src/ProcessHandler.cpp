#include "ProcessHandler.h"

ProcessHandler::ProcessHandler(const std::string& processName)
	:
	ProcName(processName),
	hProc(nullptr),
	dwProcID(0),
	dwClientBase(0),
	dwClientSize(0),
	dwEngineBase(0),
	dwEngineSize(0),
	structClientDLL{},
	structEngineDLL{}
{
}

ProcessHandler::~ProcessHandler()
{
	const auto closedStatus = CloseHandle(this->hProc);
	
	assert(closedStatus); // the handle should be active to be able to close it

#ifdef _DEBUG
	if (closedStatus)
	{
		std::cout << "Successfully closed handle: " << this->hProc << std::endl;
	}
	else
	{
		std::cout << "Failed to close handle: " << this->hProc << std::endl;
	}
#endif
}

BOOL ProcessHandler::Init()
{
	// Attach to the process.
	if (!AttachProcess()) return FALSE;

	// Get the required modules of CS:GO for accessing/writing in memory later on.
	structClientDLL = GetModule("client.dll");
	structEngineDLL = GetModule("engine.dll");
	if (structClientDLL.modBaseAddr == 0x0 || structEngineDLL.modBaseAddr == 0x0) return FALSE;

	// Store base addresses and size of all the required modules.
	dwClientBase = reinterpret_cast<DWORD>(structClientDLL.modBaseAddr);
	dwEngineBase = reinterpret_cast<DWORD>(structEngineDLL.modBaseAddr);
	dwClientSize = structClientDLL.modBaseSize;
	dwEngineSize = structEngineDLL.modBaseSize;

	return TRUE;
}

BOOL ProcessHandler::AttachProcess()
{
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

		// convert string to wstring and then to wchar for comparison
		const auto widestr = std::wstring(ProcName.begin(), ProcName.end());
		const wchar_t* w_procname = widestr.c_str();

		// Now walk the snapshot of processes, and
		// display information about each process in turn
		while (Process32Next(hProcSnap, &procEnt))
		{
			if (!_wcsicmp(w_procname, procEnt.szExeFile))
			{
				std::cout << "Process found: " << procEnt.szExeFile << " PID: " << procEnt.th32ProcessID << std::endl;

				this->dwProcID = procEnt.th32ProcessID;
				this->hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dwProcID);
				this->ProcName = ProcName;

				CloseHandle(hProcSnap);
				return TRUE;
			}
		}
	}
	else
	{
		std::cout << "Could not get snapshot of all running processes." << std::endl;
	}

	std::cout << "Process " << ProcName << " could not be found in the process list" << std::endl;

	CloseHandle(hProcSnap);
	return FALSE;
}

MODULEENTRY32 ProcessHandler::GetModule(const std::string& moduleName)
{
	assert(this->dwProcID && this->hProc); // Get module info only when there is an attached process.

	auto hModulesSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->dwProcID);

	MODULEENTRY32 modEnt;
	modEnt.dwSize = sizeof(modEnt);

	if (hModulesSnap != INVALID_HANDLE_VALUE)
	{
		// convert module name string to wstring and then to wchar for comparison
		const auto widestr = std::wstring(moduleName.begin(), moduleName.end());
		const wchar_t* w_modname = widestr.c_str();

		while (Module32Next(hModulesSnap, &modEnt))
		{
			if (!_wcsicmp(modEnt.szModule, w_modname))
			{
				std::cout << "Module found: " << moduleName << std::endl;
				CloseHandle(hModulesSnap);
				return modEnt;
			}
		}
	}
	else
	{
		std::cout << "Could not get snapshot of modules." << std::endl;
	}

	std::cout << "Module " << moduleName << " could not be found in the modules list. Returning Module entry struct with 0x0 base address." << std::endl;

	CloseHandle(hModulesSnap);
	modEnt.modBaseAddr = 0x0;
	return modEnt;
}

// Getters
std::string& ProcessHandler::GetProcessName() { return this->ProcName; }
HANDLE ProcessHandler::GetProcHandle() { return this->hProc; }
DWORD ProcessHandler::GetProcID() { return this->dwProcID; }
DWORD ProcessHandler::GetClientBase() { return this->dwClientBase; }
DWORD ProcessHandler::GetClientSize() { return this->dwClientSize; }
DWORD ProcessHandler::GetEngineBase() { return this->dwEngineBase; }
DWORD ProcessHandler::GetEngineSize() { return this->dwEngineSize; }
MODULEENTRY32 ProcessHandler::GetClient() { return this->structClientDLL; }
MODULEENTRY32 ProcessHandler::GetEngine() { return this->structEngineDLL; }