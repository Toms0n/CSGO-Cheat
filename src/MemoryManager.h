#pragma once

#include "ProcessHandler.h"
#include <iostream>
#include <memory>
#include <windows.h>
#include "Utils/Utils.h"

class MemoryManager
{
private:
	std::shared_ptr<ProcessHandler> m_Ph;

public:
	MemoryManager() = delete;
	MemoryManager(MemoryManager const&) = delete;
	MemoryManager& operator=(MemoryManager const&) = delete;
	MemoryManager(MemoryManager&&) = delete;
	MemoryManager& operator=(MemoryManager&&) = delete;

	MemoryManager(std::shared_ptr<ProcessHandler> processHandlerPtr);
	~MemoryManager();

	// I have to define template in the header file, because the compiler can't see e.g. RPM<INT> and the definition of the template in a cpp file.
	
	// Read a value (of type T) from a certain area of process memory.
	// Returns: The value found.
	template<typename T>
	T
	RPM(DWORD dwAddress)
	{
		T buffer;
		ReadProcessMemory(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), &buffer, sizeof(T), NULL);
		return buffer;
	}

	// Read a value (of type T) from a certain area of process memory of fixed size.
	// Returns: The value found.
	template <typename T>
	T
	ReadSize(DWORD dwAddress, size_t Size)
	{
		T value;
		ReadProcessMemory(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), &value, Size, NULL);
		return value;
	}

	// Read an array (of type T) from a certain area of process memory.
	// Returns: A pointer to the array found
	template <typename T>
	T*
	ReadArray(DWORD dwAddress, size_t ArraySize)
	{
		T* arr;
		if (!ReadProcessMemory(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), arr, sizeof(T) * ArraySize, NULL))
		{
			arr = nullptr;
		}
		return arr;
	}

	// Write a value (of type T) to a certain area of process memory.
	// Returns: True if the writing is successful.
	template <typename T>
	BOOL
	WPM(DWORD dwAddress, const T& ValueToWrite)
	{
		return WriteProcessMemory(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), &ValueToWrite, sizeof(T), NULL);
	}

	// Write a value (of type T) to a certain area of process memory of fixed size.
	// Returns: True if the writing is successful.
	template <typename T>
	BOOL
	WriteSize(DWORD dwAddress, T ValueToWrite, size_t Size)
	{
		return WriteProcessMemory(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), &ValueToWrite, Size, NULL);
	}

	// Write an array (of type T) to a certain area of process memory of fixed size.
	// Returns: True if the writing is successful.
	template <typename T>
	BOOL
	WriteArray(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
	{
		return WriteProcessMemory(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), ArrayToWrite, sizeof(T) * ArraySize, NULL);
	}

	// Try to write a value (of type T) to a certain area of protected process memory.
	// Returns: True if the writing is successful.
	template <typename T>
	BOOL
	WriteProtected(DWORD dwAddress, T ValueToWrite)
	{
		DWORD_PTR oldprotect;
		if (!VirtualProtectEx(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return FALSE;
		if (!Write(dwAddress, ValueToWrite)) return FALSE;
		if (!VirtualProtectEx(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), sizeof(T), oldprotect, NULL)) return FALSE;
		return TRUE;
	}

	// Try to write a value (of type T) to a certain area of protected process memory of fixed size.
	// Returns: True if the writing is successful.
	template <typename T>
	BOOL
	WriteProtectedSize(DWORD dwAddress, T ValueToWrite, size_t Size)
	{
		DWORD_PTR oldprotect;
		if (!VirtualProtectEx(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return FALSE;
		if (!WriteSize(dwAddress, ValueToWrite, Size)) return FALSE;
		if (!VirtualProtectEx(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), sizeof(T), oldprotect, NULL)) return FALSE;
		return TRUE;
	}

	// Try to write an array (of type T) to a certain area of protected process memory.
	// Returns: True if the writing is successful.
	template <typename T>
	BOOL
	WriteArrayProtected(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
	{
		DWORD_PTR oldprotect;
		if (!VirtualProtectEx(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
		if (!WriteArray(dwAddress, ArrayToWrite, ArraySize)) return false;
		if (!VirtualProtectEx(m_Ph->GetProcHandle(), reinterpret_cast<LPVOID>(dwAddress), sizeof(T), oldprotect, NULL)) return false;
		return TRUE;
	}
};