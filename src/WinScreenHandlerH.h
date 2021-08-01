#pragma once

#include <iostream>

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