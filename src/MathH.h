#pragma once

namespace Math
{
	struct Vec3
	{
		float x, y, z;

		Vec3()
			: x(0.f), y(0.f), z(0.f)
		{
		};

		Vec3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
		{
		};
	};
	
	// bone matrix of the player (with necessary padding to get the correct XYZ coordinates from memory of the game)
	// each bone of the player has this structure in memory
	struct boneMatrix
	{
		byte pad0[12];
		float x;
		byte pad1[12];
		float y;
		byte pad2[12];
		float z;
	};


	// view matrix struct of the game is stored in a 4x4 matrix
	struct viewMatrix
	{
		float matrix[16];
	};

	float distance(float x1, float y1, float x2, float y2);

	Vec3 WorldToScreen(const Vec3& boneLocation, const viewMatrix& vm);
}