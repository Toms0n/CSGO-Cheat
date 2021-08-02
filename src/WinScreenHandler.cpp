#include "WinScreenHandlerH.h"

WinScreenHandler::WinScreenHandler()
	:
	screenWidth(GetSystemMetrics(SM_CXSCREEN)),
	screenHeight(GetSystemMetrics(SM_CYSCREEN))
{
}

WinScreenHandler::~WinScreenHandler()
{
}

uint32_t WinScreenHandler::GetScreenHeight()
{
	return this->screenHeight;
}

uint32_t WinScreenHandler::GetScreenWidth()
{
	return this->screenWidth;
}