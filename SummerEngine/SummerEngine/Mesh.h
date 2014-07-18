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
	void LoadFromObj(std::string p_FileName);

	VertexGroups* GetVertexData();
	void SetVertexData(VertexGroups p_Groups);

	void ClearLoadData();


	HRESULT Render(ID3D11DeviceContext* p_DeviceContext);

	ID3D11Buffer* GetVertexBuffer(int p_Slot);
	GroupNumOfVert* GetNumOfVert();


	virtual const std::string &GetName() const;
	virtual const ResourceType GetType() const;

private:
	LoadObj* m_Mesh;
	std::string m_FileName;
	
	VertexGroups m_Groups;
	GroupNumOfVert m_NumOfVert;
	int m_NumberOfVerticesInTotal = 0;
	//std::vector<std::vector<MeshVertex>> m_Groups;
	/*GameObject gameObject;
	ID3D11Buffer* buffer;
	std::vector<ID3D11Buffer*> vertexBuffers;
	Shader shader;*/
};
