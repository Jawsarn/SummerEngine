struct Matrix
{
	float Position[3];
	float Direction[3];
	float Up[3];
};

struct FoVProjMatrix
{
	float AspectRatio;
	float FieldOfView;
	float NearZ;
	float FarZ;
};

struct OrthoProjMatrix
{
	float Width;
	float Height;
	float NearZ;
	float FarZ;
};

typedef unsigned int MatrixHandle;