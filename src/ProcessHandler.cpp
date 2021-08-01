//#include "ProcessHandlerH.h"
//#include <iostream>
//#include <Windows.h>
//#include <TlHelp32.h>
//
//// TODO: improve the logic of this class
//
//ProcessHandler::ProcessHandler()
//	:
//	Pid(0),
//	modBaseAddr(0),
//	hProc(nullptr)
//{
//}
//
//ProcessHandler::~ProcessHandler()
//{
//}
//
//void ProcessHandler::AttachProcess(const wchar_t* proc_name)
//{
//	// Take a snapshot of all processes in the system.
//	auto hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//
//	// Retrieve information about the first process,
//	// and exit if unsuccessful
//	if (hProcSnap != INVALID_HANDLE_VALUE)
//	{
//		// processes structure object
//		PROCESSENTRY32 procEnt;
//
//		// Set the size of the structure before using it.
//		procEnt.dwSize = sizeof(procEnt);
//
//		// Now walk the snapshot of processes, and
//		// display information about each process in turn
//		while (Process32Next(hProcSnap, &procEnt))
//		{
//			if (!_wcsicmp(proc_name, procEnt.szExeFile))
//			{
//				std::cout << "Process found: " << procEnt.szExeFile << " PID: " << procEnt.th32ProcessID << std::endl;
//				this->Pid = procEnt.th32ProcessID;
//				break;
//			}
//		}
//	}
//	else
//	{
//		std::cout << "Could not get snapshot of all running processes." << std::endl;
//	}
//
//	std::cout << "Process " << proc_name << " could not be found in the process list" << std::endl;
//
//	CloseHandle(hProcSnap);
//}
//
//void ProcessHandler::GetModuleBaseAddress(const wchar_t* moduleName)
//{
//	auto hModulesSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Pid);
//
//	if (hModulesSnap != INVALID_HANDLE_VALUE)
//	{
//		MODULEENTRY32 modEnt;
//		modEnt.dwSize = sizeof(modEnt);
//
//		while (Module32Next(hModulesSnap, &modEnt))
//		{
//			if (!_wcsicmp(modEnt.szModule, moduleName))
//			{
//				std::cout << "Module found: " << moduleName << std::endl;
//				this->modBaseAddr = (uintptr_t)modEnt.modBaseAddr;
//				break;
//			}
//		}
//	}
//	else
//	{
//		std::cout << "Could not get snapshot of modules." << std::endl;
//	}
//
//	std::cout << "Module " << moduleName << " could not be found in the modules list" << std::endl;
//
//	CloseHandle(hModulesSnap);
//}
//
//void ProcessHandler::OpenProc()
//{
//	OpenProcess(PROCESS_ALL_ACCESS, NULL, this->Pid);
//}