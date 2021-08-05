#include "WinScreenHandlerH.h"

WinScreenHandler::WinScreenHandler()
	:
	hWindow(FindWindowA(NULL, "Counter-Strike: Global Offensive")),
	hDeviceContext(GetDC(hWindow))
{
	SetScreenSize();
}

WinScreenHandler::~WinScreenHandler()
{
}

void WinScreenHandler::SetScreenSize()
{
	RECT rect;
	GetClientRect(hWindow, &rect);
	screenWidth = rect.right;
	screenHeight = rect.bottom;
	std::cout << "WINDOW WIDTH: " << screenWidth << " WINDOW HEIGHT: " << screenHeight << std::endl;
}

uint32_t WinScreenHandler::GetScreenHeight()
{
	return this->screenHeight;
}

uint32_t WinScreenHandler::GetScreenWidth()
{
	return this->screenWidth;
}

void WinScreenHandler::DrawLine(float StartX, float StartY, float EndX, float EndY)
{
	int a, b = 0;
	HPEN hOPen;
	HPEN hNPen = CreatePen(PS_SOLID, 2, 0x0000FF /*red*/);
	hOPen = (HPEN)SelectObject(this->hDeviceContext, hNPen);
	MoveToEx(this->hDeviceContext, StartX, StartY, NULL); //start of line
	a = LineTo(this->hDeviceContext, EndX, EndY); //end of line
	DeleteObject(SelectObject(this->hDeviceContext, hOPen));
}

void WinScreenHandler::MoveMouse(const Vector2& target, INT crosshairX, INT crosshairY)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	Input.mi.dx = target.x - crosshairX;
	Input.mi.dy = target.y - crosshairY;
	SendInput(1, &Input, sizeof(INPUT));
}