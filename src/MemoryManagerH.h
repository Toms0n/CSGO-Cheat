#pragma once

#include "ProcessHandlerH.h"
#include <iostream>
#include <memory>
#include <windows.h>

class MemoryManager
{
private:
	std::shared_ptr<ProcessHandler> m_Ph;

public:
	MemoryManager(std::shared_ptr<ProcessHandler> processHandlerPtr);
	~MemoryManager();

	// Read a value (of type T) from a certain area of process memory.
	// Returns: The value found.
	template<typename T>
	T 
	RPM(DWORD dwAddress);


	// Read a value (of type T) from a certain area of process memory of fixed size.
	// Returns: The value found.
	template <class T>
	T
	ReadSize(DWORD dwAddress, size_t Size);

	// Read an array (of type T) from a certain area of process memory.
	// Returns: A pointer to the array found
	template <class T>
	T*
	ReadArray(DWORD dwAddress, size_t ArraySize);

	// Write a value (of type T) to a certain area of process memory.
	// Returns: True if the writing is successful.
	template <class T>
	BOOL
	Write(DWORD dwAddress, T ValueToWrite);

	// Write a value (of type T) to a certain area of process memory of fixed size.
	// Returns: True if the writing is successful.
	template <class T>
	BOOL
	WriteSize(DWORD dwAddress, T ValueToWrite, size_t Size);

	// Write an array (of type T) to a certain area of process memory of fixed size.
	// Returns: True if the writing is successful.
	template <class T>
	BOOL
	WriteArray(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize);

	// Try to write a value (of type T) to a certain area of protected process memory.
	// Returns: True if the writing is successful.
	template <class T>
	BOOL
	WriteProtected(DWORD dwAddress, T ValueToWrite);

	// Try to write a value (of type T) to a certain area of protected process memory of fixed size.
	// Returns: True if the writing is successful.
	template <class T>
	BOOL
	WriteProtectedSize(DWORD dwAddress, T ValueToWrite, size_t Size);

	// Try to write an array (of type T) to a certain area of protected process memory.
	// Returns: True if the writing is successful.
	template <class T>
	BOOL
	WriteArrayProtected(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize);
};