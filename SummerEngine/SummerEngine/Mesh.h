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
	typedef std::vector<std::vector<int>> IndicesGroups;

	Mesh();
	~Mesh();

	void Release();
	HRESULT CreateMeshBuffers(ID3D11Device* p_Device);

	int GetNumOfVert(int p_Slot);

	ID3D11Buffer* GetVertexBuffer(int p_Slot);
	std::vector<ID3D11Buffer*> GetVertexBuffers();
	VertexGroups* GetVertexData();
	void SetVertexData(VertexGroups p_Groups);
	void SetIndexData(IndicesGroups* p_IndexGroups);
	void ClearLoadData();

	virtual const std::string &GetName() const;
	virtual const ResourceType GetType() const;

private:
	VertexGroups m_Groups;
	IndicesGroups m_IndicesGroups;
	ID3D11Buffer* m_Buffer;
	std::vector<ID3D11Buffer*> m_VertexBuffers;
};
