#include "CshoHackHeader.h"

int main()
{
	const wchar_t* proc_name = L"csgo.exe";
	const DWORD hProc = AttachProcess(proc_name);
	const uintptr_t modBaseAddr = GetModuleBaseAddress(hProc, proc_name);

}