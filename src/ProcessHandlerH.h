//#pragma once
//
//#include <Windows.h>
//
//// TODO: improve the logic of this class
//
//class ProcessHandler
//{
//private:
//	DWORD Pid;
//	uintptr_t modBaseAddr;
//	HANDLE hProc;
//
//public:
//	ProcessHandler();
//	~ProcessHandler();
//
//	/*
//	* Traverse the process list to get the handle of the given process name.
//	*
//	* [proc_name] => the name of the process of which the handle is required
//	*/
//	void AttachProcess(const wchar_t* proc_name);
//
//	/*
//	* Traverse the module list to get the base address of the given module name.
//	*
//	* [hProc] => the handle of the processes of the game
//	* [modName] => the module name to get the base address of
//	*
//	* [RETURNS] => pointer to the base address of the module
//	*/
//	void GetModuleBaseAddress(const wchar_t* modName);
//
//	void OpenProc();
//};
