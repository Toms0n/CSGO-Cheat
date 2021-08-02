#include "ProcessHandlerH.h"

ProcessHandler::ProcessHandler()
{
	if (Init())
	{
		std::cout << "Sucessfully initialized ProcessHandler with process name: " << ProcName << std::endl;
	}
	else
	{
		std::cout << "Failed to initialize ProcessHandler to process " << ProcName << std::endl;
	}
}

ProcessHandler::~ProcessHandler()
{
	assert(this->h_Proc); // the handle should be active to be able to close it

	if (CloseHandle(this->h_Proc))
	{
		std::cout << "Sucessfully closed handle: " << this->h_Proc << std::endl;
	}
	else
	{
		std::cout << "Failed to close handle: " << this->h_Proc << std::endl;
	}
}

BOOL ProcessHandler::Init()
{
	// Attach to the process.
	if (!AttachProcess("csgo.exe")) return FALSE;

	// Get the required modules of CS:GO for accessing/writing in memory later on.
	ClientDLL = GetModule("client.dll");
	EngineDLL = GetModule("engine.dll");
	if (ClientDLL.modBaseAddr == 0x0 || EngineDLL.modBaseAddr == 0x0) return FALSE;

	// Store base addresses and size of all the required modules.
	ClientBase = reinterpret_cast<DWORD>(ClientDLL.modBaseAddr);
	EngineBase = reinterpret_cast<DWORD>(EngineDLL.modBaseAddr);
	ClientSize = ClientDLL.modBaseSize;
	EngineSize = EngineDLL.modBaseSize;

	return TRUE;
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

MODULEENTRY32 ProcessHandler::GetModule(const std::string& moduleName)
{
	assert(this->dw_ProcID && this->h_Proc); // Get module info only when there is an attached process.

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

// Getters
std::string& ProcessHandler::GetProcessName() { return this->ProcName; }
HANDLE ProcessHandler::GetProcHandle() { return this->h_Proc; }
DWORD ProcessHandler::GetProcID() { return this->dw_ProcID; }
DWORD ProcessHandler::GetClientBase() { std::cout << "Client Base Addr: " << this->ClientBase << std::endl; return this->ClientBase; }
DWORD ProcessHandler::GetClientSize() { return this->ClientSize; }
DWORD ProcessHandler::GetEngineBase() { return this->EngineBase; }
DWORD ProcessHandler::GetEngineSize() { return this->EngineSize; }
MODULEENTRY32 ProcessHandler::GetClient() { return this->ClientDLL; }
MODULEENTRY32 ProcessHandler::GetEngine() { return this->EngineDLL; }