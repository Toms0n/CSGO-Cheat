#include "ProcessHandlerH.h"

ProcessHandler::ProcessHandler()
{
	// TODO: maybe init the private data?
}

ProcessHandler::~ProcessHandler()
{
	ClearHandle();
}

BOOL ProcessHandler::AttachProcess(const std::string& proc_name)
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
		const auto widestr = std::wstring(proc_name.begin(), proc_name.end());
		const wchar_t* w_procname = widestr.c_str();

		// Now walk the snapshot of processes, and
		// display information about each process in turn
		while (Process32Next(hProcSnap, &procEnt))
		{
			if (!_wcsicmp(w_procname, procEnt.szExeFile))
			{
				std::cout << "Process found: " << procEnt.szExeFile << " PID: " << procEnt.th32ProcessID << std::endl;

				this->dw_ProcID = procEnt.th32ProcessID;
				this->h_Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dw_ProcID);
				this->ProcName = proc_name;

				CloseHandle(hProcSnap);
				return TRUE;
			}
		}
	}
	else
	{
		std::cout << "Could not get snapshot of all running processes." << std::endl;
	}

	std::cout << "Process " << proc_name << " could not be found in the process list" << std::endl;

	CloseHandle(hProcSnap);
	return FALSE;
}

MODULEENTRY32 ProcessHandler::GetModuleBaseAddress(const std::string& moduleName)
{
	auto hModulesSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->dw_ProcID);

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

BOOL ProcessHandler::ClearHandle()
{
	return (CloseHandle(this->h_Proc) == TRUE);
}

// Getters
std::string ProcessHandler::GetProcessName() { return this->ProcName; }
HANDLE ProcessHandler::GetProcHandle() { return this->h_Proc; }
DWORD ProcessHandler::GetProcID() { return this->dw_ProcID; }
DWORD ProcessHandler::GetClientBase() { return this->ClientBase; }
DWORD ProcessHandler::GetClientSize() { return this->ClientSize; }
DWORD ProcessHandler::GetEngineBase() { return this->EngineBase; }
DWORD ProcessHandler::GetEngineSize() { return this->EngineSize; }
MODULEENTRY32 ProcessHandler::GetClient() { return this->ClientDLL; }
MODULEENTRY32 ProcessHandler::GetEngine() { return this->EngineDLL; }