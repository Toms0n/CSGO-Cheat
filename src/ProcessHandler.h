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

	HANDLE hProc;	// HANDLE to the attached process
	
	DWORD dwProcID;  // Process ID of the attached process
	DWORD dwClientBase; // Base address of Client.dll
	DWORD dwClientSize; // Base size of Client.dll (in bytes)
	DWORD dwEngineBase; // Base address of Engine.dll
	DWORD dwEngineSize; // Base size of Engine.dll (in bytes)
	
	MODULEENTRY32 structClientDLL; // Struct for Client.dll
	MODULEENTRY32 structEngineDLL; // Struct for Engine.dll

public:
	ProcessHandler() = delete;
	ProcessHandler(ProcessHandler const&) = delete;
	ProcessHandler& operator=(ProcessHandler const&) = delete;
	ProcessHandler(ProcessHandler&&) = delete;
	ProcessHandler& operator=(ProcessHandler&&) = delete;

	ProcessHandler(const std::string& processName);

	// Close the HANDLE of the object.
	// The HANDLE must be closed, otherwise there is a memory leak.
	~ProcessHandler();

	/* 
	* Initializes the class to read from and write to the given process memory.
	* [RETURNS]: True if the initialization is successful.
	*/
	BOOL Init();

	/*
	* Traverse the process list to get the handle of the given process name.
	* Once attached it sets the hProcess and the dwProcessID of the class.
	* 
	* [RETURNS]: True if the process is found and valid.
	*/
	BOOL AttachProcess();

	/*
	* Traverse the module list to get the base address of the given module name.
	* Get a module by name from the attached process (if attached).
	* 
	* [modName]: the module name to get the base address of
	*
	* [RETURNS]: Module entry struct for the module found. Base address = 0x0 if not found.
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