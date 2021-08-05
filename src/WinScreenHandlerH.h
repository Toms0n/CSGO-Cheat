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

	void SetScreenSize();
	uint32_t GetScreenWidth();
	uint32_t GetScreenHeight();

	//This function is optional for debugging.
	void DrawLine(float StartX, float StartY, float EndX, float EndY);

	void MoveMouse(const Vector2& target, INT crosshairX, INT crosshairY);
};