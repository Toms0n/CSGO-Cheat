#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <cassert> 
#include <memory>

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

	// Calls Init() to initialize the ProcessHandler.
	ProcessHandler();

	// Close the HANDLE of the object.
	// The HANDLE must be closed, otherwise there is a memory leak.
	~ProcessHandler();

	// Initializes the class to read from and write to the given process memory.
	// Returns: True if the initialization is successful.
	BOOL Init(const std::string& processName = "csgo.exe");

	/*
	* Traverse the process list to get the handle of the given process name.
	* Once attached it sets the hProcess and the dwProcessID of the class.
	* 
	* [procName] => the name of the process of which the handle is required
	* 
	* [RETURNS] => True if the process is found and valid.
	*/
	BOOL AttachProcess(const std::string& procName);

	/*
	* Traverse the module list to get the base address of the given module name.
	* Get a module by name from the attached process (if attached).
	* 
	* [hProc] => the handle of the processes of the game
	* [modName] => the module name to get the base address of
	*
	* RETURNS: Module entry struct for the module found. Base address = 0x0 if not found.
	*/
	MODULEENTRY32 GetModule(const std::string& modName);

	// Getters
	std::string& GetProcessName();
	HANDLE GetProcHandle();
	DWORD GetProcID();
	DWORD GetClientBase();
	DWORD GetClientSize();
	DWORD GetEngineBase();
	DWORD GetEngineSize();
	MODULEENTRY32 GetClient();
	MODULEENTRY32 GetEngine();
};