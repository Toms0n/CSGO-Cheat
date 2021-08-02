#pragma once

#include <iostream>
#include <windows.h>

class WinScreenHandler
{
private:
	uint32_t screenWidth;
	uint32_t screenHeight;
public:
	WinScreenHandler();
	~WinScreenHandler();

	uint32_t GetScreenWidth();
	uint32_t GetScreenHeight();
};