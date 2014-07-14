#pragma once
#include "LoadObj.h"
#include "Math.h"

class Mesh
{
public:
	Mesh();
	~Mesh();


private:
	LoadObj* mesh;
	void Release();
	HRESULT CreateMesh(ID3D11Device* p_device, char* p_fileName);

	struct MeshVertex
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT2 texCoord;

		MeshVertex()
		{
			position = XMFLOAT3(0, 0, 0);
			normal = XMFLOAT3(0, 0, 0);
			texCoord = XMFLOAT2(0, 0);
		}
	};
};
