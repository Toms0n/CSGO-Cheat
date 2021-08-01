#include "MemoryManagerH.h"
#include <Windows.h>

MemoryManager::MemoryManager()
	: m_Ph(ProcessHandler())
{
}

MemoryManager::~MemoryManager()
{
}

template<typename T>
T 
MemoryManager::RPM(SIZE_T address)
{
	T buffer;
	ReadProcessMemory(m_Ph.hProc, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}