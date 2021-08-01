#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>


class ProcessHandler
{
private:
	std::string ProcName; // Name of the attached process

	HANDLE h_Proc;	// HANDLE to the attached process
	
	DWORD dw_ProcID;  // Process ID of the attached process
	DWORD ClientBase; // Base address of Client.dll
	DWORD ClientSize; // Base size of Client.dll (in bytes)
	DWORD EngineBase; // Base address of Engine.dll
	DWORD EngineSize; // Base size of Engine.dll (in bytes)
	
	MODULEENTRY32 ClientDLL; // Struct for Client.dll
	MODULEENTRY32 EngineDLL; // Struct for Engine.dll

public:
	ProcessHandler();
	~ProcessHandler();

	/*
	* Traverse the process list to get the handle of the given process name.
	* Once attached it sets the hProcess and the dwProcessID of the class.
	* 
	* [proc_name] => the name of the process of which the handle is required
	* 
	* [RETURNS] => True if the process is found and valid.
	*/
	BOOL AttachProcess(const std::string& proc_name);

	/*
	* Traverse the module list to get the base address of the given module name.
	* Get a module by name from the attached process (if attached).
	* 
	* [hProc] => the handle of the processes of the game
	* [modName] => the module name to get the base address of
	*
	* [RETURNS] => Module entry struct for the module found. Base address = 0x0 if not found.
	*/
	MODULEENTRY32 GetModuleBaseAddress(const std::string& modName);

	// Getters
	std::string GetProcessName();
	HANDLE GetProcHandle();
	DWORD GetProcID();
	DWORD GetClientBase();
	DWORD GetClientSize();
	DWORD GetEngineBase();
	DWORD GetEngineSize();
	MODULEENTRY32 GetClient();
	MODULEENTRY32 GetEngine();

	// Close the HANDLE of the object.
	// The HANDLE must be closed, otherwise there is a memory leak.
	// Returns: True if the function is successful.
	BOOL ClearHandle();
};