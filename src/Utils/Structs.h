// This header defines several non-namespaced methods and structs that can help in making the cheat
#pragma once

constexpr auto PLAYERS_INDEX_SEPERATION = 0x10; // player pointers in csgo are seperated with 0x10 in the entity list
constexpr auto GLOW_IDX_SEPERATION = 0x38; // space between each glow index of player
constexpr auto GLOW_VALUES_OFFSET = 0x8; // offset to skip first 8 byts (that could crash the game if it is being written to)

// Struct definition for an RGBA color
struct RGBA
{
	float r, g, b, a;
};

struct GlowStruct
{
	//int m_nNextFreeSlot;
	//DWORD pEnt;
	RGBA rbga; // RGB values with alpha as A
	//bool m_bGlowAlphaCappedByRenderAlpha;
	//float m_flGlowAlphaFunctionOfMaxVelocity;
	//float m_flGlowAlphaMax;
	//float m_flGlowPulseOverdrive;
	uint8_t unknown1[16];
	bool renderOccluded;
	bool renderUnoccluded;
	bool fullBloom;
	//uint8_t unknown2[5];
	//int glowStyle;
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