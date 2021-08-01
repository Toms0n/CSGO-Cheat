#pragma once

#include "ProcessHandlerH.h"
#include <Windows.h>

class MemoryManager
{
private:
	ProcessHandler m_Ph;

public:
	MemoryManager();
	~MemoryManager();

	template<typename T>
	T 
	RPM(SIZE_T address);
};