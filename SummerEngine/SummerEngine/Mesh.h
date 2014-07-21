#pragma once
#include "LoadObj.h"
#include "Math.h"
#include "Resource.h"

class Mesh:public Resource
{
public:
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
	typedef std::vector<std::vector<MeshVertex>> VertexGroups;
	typedef std::vector<int> GroupNumOfVert;


	Mesh();
	~Mesh();

	void Release();
	HRESULT CreateMeshBuffers(ID3D11Device* p_Device);

	VertexGroups* GetVertexData();
	void SetVertexData(VertexGroups p_Groups);
	void ClearLoadData();

	ID3D11Buffer* GetVertexBuffer(int p_Slot);
	int GetNumOfVert(int p_Slot);


	virtual const std::string &GetName() const;
	virtual const ResourceType GetType() const;

private:
	VertexGroups m_Groups;
	ID3D11Buffer* buffer;//test
	std::vector<ID3D11Buffer*> vertexBuffers;//test/
};
