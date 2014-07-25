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
	HRESULT CreateMeshBuffers();

	int GetNumOfVert(int p_Slot);
	int GetNumOfIndecies(int p_Group);

	int GetNumOfBuffers();

	ID3D11Buffer* GetVertexBuffer(int p_Slot);
	ID3D11Buffer* GetIndexBuffer(int p_Slot);
	std::vector<ID3D11Buffer*> GetVertexBuffers();
	IndicesGroups* GetIndexData();
	VertexGroups* GetVertexData();
	void SetVertexData(VertexGroups p_Groups);
	void SetIndexData(IndicesGroups p_IndexGroups);
	void ClearLoadData();


	virtual void SetName(std::string p_Name);
	virtual const std::string GetName();
	virtual const ResourceType GetType() const;

private:
	VertexGroups m_Groups;
	IndicesGroups m_IndicesGroups;
	
	std::vector<ID3D11Buffer*> m_VertexBuffers;
	std::vector<int> m_NumOfVertex;
	std::vector<int> m_NumOfIndex;
	std::vector<ID3D11Buffer*> m_IndexBuffers;
};
