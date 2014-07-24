#include "Rectangles.h"

Rectangles::Rectangles()
{
}

Rectangles::Rectangles(ID3D11Device* device)
{
	//Buffers
	vertexBuffer = NULL;
	constantBuffer = NULL;
	CreateButton(device);

	//WORLD MATRIX
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	XMMATRIX scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX translation = XMMatrixTranslation(1.0f, 1.0f, 0.0f);
	XMMATRIX world = XMMatrixTranspose(rotation * scale * translation);
	cbPerObj.WORLD = world;
}

Rectangles::~Rectangles()
{
}

HRESULT Rectangles::CreateButton(ID3D11Device* device)
{
	Vertex Rect[4] =
	{
		/*POSITION*/-0.25f, -0.25f, 0,	/*NORMAL*/0, 0, -1,/*UV*/0, 1,
		/*POSITION*/ -0.25f, 0.25f, 0,	/*NORMAL*/0, 0, -1,/*UV*/0, 0,
		/*POSITION*/ 0.25f, -0.25f, 0,  /*NORMAL*/0, 0, -1,/*UV*/1, 1,
		/*POSITION*/ 0.25f, 0.25f, 0,  /*NORMAL*/0, 0, -1,/*UV*/1, 0,
	};

	//Set vertex description
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.MiscFlags = 0;
	bufferDesc.ByteWidth = sizeof(Rect);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = Rect;
	HRESULT hr = device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);


	//CREATE BUFFER FOR Constantbuffer (WORLD)
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = device->CreateBuffer(&cbbd, NULL, &constantBuffer);
	if (FAILED(hr))
		return hr;
	return hr;
}

HRESULT Rectangles::Update(float deltaTime)
{
	return S_OK;
}

HRESULT Rectangles::Render(ID3D11DeviceContext* deviceContext)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//draw triangle
	UINT32 vertexSize = sizeof(Vertex);
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexSize, &offset);

	deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &cbPerObj, 0, 0);
	deviceContext->VSSetConstantBuffers(1, 1, &constantBuffer);

	deviceContext->Draw(4, 0);

	return S_OK;
}