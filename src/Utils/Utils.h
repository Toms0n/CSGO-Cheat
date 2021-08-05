/// Utils.h
// This header defines several non-namespaced methods and structs that can help in making the cheat

#pragma once

//#include <iostream>
//#include <string>

// Struct definition for an RGBA color
// Kind of rough, can be improved ofc
struct RGBA
{
	float r, g, b, a;
};

// Struct definition for a glow object
struct GlowObject
{
	DWORD pEntity;
	RGBA rbga;
	/*float r;
	float g;
	float b;
	float a;*/
	uint8_t unk1[16];
	bool RenderWhenOccluded;
	bool RenderWhenUnoccluded;
	bool FullBloom;
	uint8_t unk2[14];
};


// Struct definition for the WorldToScreenMatrix 4x4
// Since CS:GO uses DirectX on windows, the X,Y,Z vectors in the matrix are row major.
// X-Axis is on row 0, Y-Axis is on row 1, Z-axis is on row 2 and translation vector is on row 3
struct viewMatrix
{
	float flMatrix[4][4];
};

// Struct definition for the 3x4 bone matrix of the player
// (with necessary padding to get the correct XYZ coordinates from memory of the game)
// Each bone of the player has this structure in memory
struct boneMatrix
{
	UINT pad0[3];	// padding from [0][0] tot [0][2]
	float x;		// [0][3] entry contains the x coordinate of the bone
	UINT pad1[3];	// padding from [1][0] tot [1][2]
	float y;		// [1][3] entry contains the y coordinate of the bone
	UINT pad2[3];	// padding from [2][0] tot [2][2]
	float z;		// [2][3] entry contains the z coordinate of the bone
};

enum ClientStates : int
{
	IN_LOBBY = 0,
	LOADING = 1,
	CONNECTING = 2,
	CONNECTED = 5,
	IN_GAME = 6
};

// Converts a const std::string to const wchar_t*
//static const wchar_t* StringToWChar(const std::string& str)
//{
//	const auto widestr = std::wstring(str.begin(), str.end());
//	return widestr.c_str();
//}