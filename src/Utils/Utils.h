/// Utils.h
// This header defines several non-namespaced methods and structs that can help in making the cheat

#pragma once

#include <iostream>
#include <string>

// Struct definition for a glow object
struct GlowObject_t
{
	DWORD pEntity;
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool RenderWhenOccluded;
	bool RenderWhenUnoccluded;
	bool FullBloom;
	uint8_t unk2[14];
};

// Struct definition for an RGBA color
// Kind of rough, can be improved ofc
struct RGBA
{
	float r, g, b, a;
};

// Struct definition for the WorldToScreenMatrix 4x4
typedef struct
{
	float flMatrix[4][4];
} WorldToScreenMatrix_t;

// Converts a const std::string to const wchar_t*
//static const wchar_t* StringToWChar(const std::string& str)
//{
//	const auto widestr = std::wstring(str.begin(), str.end());
//	return widestr.c_str();
//}