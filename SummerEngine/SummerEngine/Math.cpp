#include "Math.h"


Math::Math()
{
}


Math::~Math()
{
}

XMFLOAT3 Math::Add2XMFLOAT3(XMFLOAT3* a, XMFLOAT3* b)
{
	XMVECTOR t_a = XMLoadFloat3(a);
	XMVECTOR t_b = XMLoadFloat3(b);

	XMFLOAT3 result;
	XMStoreFloat3(&result, t_a + t_b);
	return result;
}

XMFLOAT4X4 Math::MultiPly2XMFLOAT4X4(XMFLOAT4X4* a, XMFLOAT4X4* b)
{
	XMMATRIX t_a = XMLoadFloat4x4(a);
	XMMATRIX t_b = XMLoadFloat4x4(b);

	XMFLOAT4X4 result;
	XMStoreFloat4x4(&result, t_a*t_b);
	return result;
}

XMFLOAT4X4 Math::MultiPlyXMFLOAT4X4XMMAATRIX(XMFLOAT4X4* a, XMMATRIX* b)
{
	XMMATRIX t_a = XMLoadFloat4x4(a);
	XMMATRIX t_ab = t_a * (*b);

	XMFLOAT4X4 result;
	XMStoreFloat4x4(&result, t_ab);

	return result;
}