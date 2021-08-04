#include "MemoryManagerH.h"

MemoryManager::MemoryManager(std::shared_ptr<ProcessHandler> processHandlerPtr)
	: m_Ph(processHandlerPtr)
{
}

MemoryManager::~MemoryManager()
{
}