#include "MemoryManagerH.h"

MemoryManager::MemoryManager(std::shared_ptr<ProcessHandler> processHandlerPtr)
	: m_Ph(processHandlerPtr)
{
}

MemoryManager::~MemoryManager()
{
}

template<typename T>
T 
MemoryManager::RPM(DWORD dwAddress)
{
	T buffer;
	ReadProcessMemory(m_Ph.hProc, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

template <class T> 
T 
MemoryManager::ReadSize(DWORD dwAddress, size_t Size)
{
	T value;
	ReadProcessMemory(hProcess, (LPVOID)dwAddress, &value, Size, NULL);
	return value;
}

template <class T>
T*
MemoryManager::ReadArray(DWORD dwAddress, size_t ArraySize)
{
	T* arr;
	if (!ReadProcessMemory(hProcess, (LPVOID)dwAddress, arr, sizeof(T) * ArraySize, NULL))
	{
		arr = nullptr;
	}
	return arr;
}

template <class T>
BOOL
MemoryManager::Write(DWORD dwAddress, T ValueToWrite)
{
	return WriteProcessMemory(hProcess, (LPVOID)dwAddress, &ValueToWrite, sizeof(T), NULL) == TRUE;
}

template <class T>
BOOL
MemoryManager::WriteSize(DWORD dwAddress, T ValueToWrite, size_t Size)
{
	return WriteProcessMemory(hProcess, (LPVOID)dwAddress, &ValueToWrite, Size, NULL) == TRUE;
}

template <class T>
BOOL
MemoryManager::WriteArray(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
{
	return WriteProcessMemory(hProcess, (LPVOID)dwAddress, ArrayToWrite, sizeof(T) * ArraySize, NULL) == TRUE;
}

template <class T>
BOOL
MemoryManager::WriteProtected(DWORD dwAddress, T ValueToWrite)
{
	DWORD_PTR oldprotect;
	if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return FALSE;
	if (!Write(dwAddress, ValueToWrite)) return FALSE;
	if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), oldprotect, NULL)) return FALSE;
	return TRUE;
}

template <class T>
BOOL
MemoryManager::WriteProtectedSize(DWORD dwAddress, T ValueToWrite, size_t Size)
{
	DWORD_PTR oldprotect;
	if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return FALSE;
	if (!WriteSize(dwAddress, ValueToWrite, Size)) return FALSE;
	if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), oldprotect, NULL)) return FALSE;
	return TRUE;
}

template <class T>
BOOL
MemoryManager::WriteArrayProtected(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
{
	DWORD_PTR oldprotect;
	if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
	if (!WriteArray(dwAddress, ArrayToWrite, ArraySize)) return false;
	if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), oldprotect, NULL)) return false;
	return TRUE;
}