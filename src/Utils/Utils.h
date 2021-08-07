#pragma once

#include <iostream>
#include <string>

// Converts a const std::string to const wchar_t*
static const wchar_t* StringToWChar(const std::string& str)
{
	const auto widestr = std::wstring(str.begin(), str.end());
	return widestr.c_str();
}