#pragma once
#include <DirectXMath.h>
#include <D3D11.h>

using namespace DirectX;
class Math
{
public:
	Math();
	~Math();

	//XMFLOAT
	static XMFLOAT3 Add2XMFLOAT3(XMFLOAT3* a, XMFLOAT3* b);
	static XMFLOAT4X4 MultiPly2XMFLOAT4X4(XMFLOAT4X4* a, XMFLOAT4X4* b);

	//XMMATRIX
	static XMFLOAT4X4 MultiPlyXMFLOAT4X4XMMAATRIX(XMFLOAT4X4* a, XMMATRIX* b);

	//random functions
	static float RandF();
	static float RandF(float a, float b);
	
};

