#pragma once
#include "Math.h"

class Rectangles
{
public:
	Rectangles();
	Rectangles(ID3D11Device* device);
	~Rectangles();

	struct Vertex
	{
		float Pos[3];
		float Normal[3];
		float TexCoord[2];
	};

	HRESULT CreateButton(ID3D11Device* device);
	HRESULT Update(float deltaTime);
	HRESULT Render(ID3D11DeviceContext* deviceContext);

private:
	ID3D11Buffer* vertexBuffer;

	XMMATRIX world;

	struct cbPerObject
	{
		XMMATRIX  WORLD;
	}cbPerObj;

	ID3D11Buffer* constantBuffer;
};

