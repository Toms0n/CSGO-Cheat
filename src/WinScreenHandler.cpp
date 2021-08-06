#include "WinScreenHandler.h"

WinScreenHandler::WinScreenHandler()
	:
	hWindow(nullptr),
	hDeviceContext(nullptr),
	screenWidth(0),
	screenHeight(0)
{
}

WinScreenHandler::~WinScreenHandler()
{
}

BOOL WinScreenHandler::Init()
{
	// TODO: this can be done in a better way than hard-coding string of the game here
	hWindow = FindWindowA(NULL, "Counter-Strike: Global Offensive");
	hDeviceContext = GetDC(hWindow);

	if (hWindow == NULL || hDeviceContext == NULL) return FALSE;

	RECT rect;
	const auto retVal = GetClientRect(hWindow, &rect);
	screenWidth = rect.right;
	screenHeight = rect.bottom;

	if (!retVal || screenHeight == 0 || screenWidth == 0) return FALSE;

#ifdef _DEBUG
	std::cout << "WINDOW WIDTH: " << screenWidth << " WINDOW HEIGHT: " << screenHeight << std::endl;
#endif

	return TRUE;
}

uint32_t WinScreenHandler::GetScreenHeight()
{
	return screenHeight;
}

uint32_t WinScreenHandler::GetScreenWidth()
{
	return screenWidth;
}

#ifdef _DEBUG
void WinScreenHandler::DrawLine(float StartX, float StartY, float EndX, float EndY)
{
	// TODO: this method is inefficient since each object is created and destroyed each time
	// TODO: something is drawn
	int a, b = 0;
	HPEN hOPen;
	HPEN hNPen = CreatePen(PS_SOLID, 2, 0x0000FF /*red*/);
	hOPen = (HPEN)SelectObject(this->hDeviceContext, hNPen);
	MoveToEx(this->hDeviceContext, StartX, StartY, NULL); //start of line
	a = LineTo(this->hDeviceContext, EndX, EndY); //end of line
	DeleteObject(SelectObject(this->hDeviceContext, hOPen));
}
#endif