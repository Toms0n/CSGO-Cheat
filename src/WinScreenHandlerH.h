#pragma once

#include <iostream>
#include <windows.h>
#include "Utils/Maths.h"

class WinScreenHandler
{
private:
	uint32_t screenWidth;
	uint32_t screenHeight;
	HWND hWindow;
	HDC hDeviceContext;

public:
	WinScreenHandler();
	~WinScreenHandler();

	BOOL Init();

	uint32_t GetScreenWidth();
	uint32_t GetScreenHeight();

#ifdef _DEBUG
	void DrawLine(float StartX, float StartY, float EndX, float EndY);
#endif

};