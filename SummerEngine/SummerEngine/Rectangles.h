#pragma once
#include "Math.h"

class Rectangles
{
public:
	Rectangles();
	Rectangles(ID3D11Device* p_Device);
	~Rectangles();

	struct Vertex
	{
		float Pos[3];
		float Normal[3];
		float TexCoord[2];
	};

	HRESULT CreateButton(ID3D11Device* p_Device);
	HRESULT Update(float p_DeltaTime);
	HRESULT Render(ID3D11DeviceContext* p_DeviceContext);

private:
	ID3D11Buffer* m_VertexBuffer;

	XMMATRIX m_World;

	struct cbPerObject
	{
		XMMATRIX  WORLD;
	}m_WorldStruct;

	ID3D11Buffer* m_ConstantBuffer;
};

