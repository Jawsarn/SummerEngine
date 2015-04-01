#pragma once
struct Vec3
{
	float x;
	float y;
	float z;

	Vec3()
	{
		x = 0; y = 0; z = 0;
	}
	Vec3(float _x, float _y, float _z)
	{
		x = _x; y = _y; z = _z;
	}
};

struct Vec2
{
	float x;
	float y;
	Vec2()
	{
		x = 0; y = 0;
	}
	Vec2(float _x, float _y)
	{
		x = _x; y = _y;
	}
};

struct Matrix
{
	Vec3 Position;
	Vec3 Direction;
	Vec3 Up;
	Matrix()
	{
		Position = Vec3(0,0,0);
		Direction = Vec3(0, 0, 0);
		Up = Vec3(0, 0, 0);
	}

	Matrix(Vec3 p_Position, Vec3 p_Direction, Vec3 p_Up)
	{
		Position = p_Position;
		Direction = p_Direction;
		Up = p_Up;
	}
};

struct FoVProjMatrix
{
	float AspectRatio;
	float FieldOfView;
	float NearZ;
	float FarZ;

	FoVProjMatrix()
	{

	}
	FoVProjMatrix(float p_AspectRatio, float p_FieldOfView, float p_NearZ, float p_FarZ)
	{
		AspectRatio = p_AspectRatio;
		FieldOfView = p_FieldOfView;
		NearZ = p_NearZ;
		FarZ = p_FarZ;
	}
};

struct OrthoProjMatrix
{
	float Width;
	float Height;
	float NearZ;
	float FarZ;
};

typedef unsigned int MatrixHandle;