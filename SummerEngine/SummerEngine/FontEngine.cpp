#include "FontEngine.h"


FontEngine::FontEngine()
{
}


FontEngine::~FontEngine()
{
}

void FontEngine::Release()
{
	//if (m_Texture)
	//{
	//	delete m_Texture;
	//	m_Texture = nullptr;
	//}
	if (m_VertexBuffer)
	{
		delete (m_VertexBuffer);
		m_VertexBuffer = nullptr;
	}
	if (m_ColorMapSampler)
	{
		delete(m_ColorMapSampler);
		m_ColorMapSampler = nullptr;
	}
}


bool FontEngine::LoadContent(ID3D11Device* p_Device)
{
	m_Texture = nullptr;
	std::wstring t_FontFileName = L"../SummerEngine/Graphics/Fonts/font.dds";

	ID3D11Resource* t_Resource;
	HRESULT t_HR = CreateDDSTextureFromFile(p_Device, t_FontFileName.c_str(), &t_Resource, &m_Texture);
	if (FAILED(t_HR))
	{
		MessageBox(nullptr, L"Could not load font-texture",L"Error",MB_ICONERROR | MB_OK);
		return false;
	}
	if (t_Resource)
	{
		t_Resource->Release();
		t_Resource = nullptr;
	}

	//Sampler
	D3D11_SAMPLER_DESC T_ColorMapDesc;
	ZeroMemory(&T_ColorMapDesc, sizeof(T_ColorMapDesc));
	T_ColorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	T_ColorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	T_ColorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	T_ColorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	T_ColorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	T_ColorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	t_HR = p_Device->CreateSamplerState(&T_ColorMapDesc, &m_ColorMapSampler);

	if (FAILED(t_HR))
	{
		MessageBox(nullptr, L"Could not create sampler state", L"Error", MB_ICONERROR | MB_OK);
		return false;
	}


	D3D11_BUFFER_DESC t_VertexDesc;
	ZeroMemory(&t_VertexDesc, sizeof(t_VertexDesc));
	t_VertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	t_VertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	t_VertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	int t_AmountOfVerticesInRect = 6;
	const int t_SpriteSize = sizeof(VertexType)* t_AmountOfVerticesInRect;
	const int t_MaxLetters = 24;

	t_VertexDesc.ByteWidth = t_SpriteSize * t_MaxLetters; //This many vertices is needed
	//Creating the vertex buffer
	t_HR = p_Device->CreateBuffer(&t_VertexDesc, 0, &m_VertexBuffer);

	if (FAILED(t_HR))
	{
		MessageBox(nullptr, L"Could not Create vertex-buffer", L"Error", MB_ICONERROR | MB_OK);
		return false;
	}

	return true;
}


void FontEngine::Update(float p_DeltaTime)
{
	//Update crap here :P
}

bool FontEngine::DrawString(ID3D11DeviceContext* p_DeviceContext, char* p_Text, float p_StartX, float p_StartY)
{
	//Size of a sprite (one)
	const int t_SizeOfSprite = sizeof(VertexType)* 6;

	// Dynamic buffer
	const int t_MaxLetters = 24;

	int t_Length = strlen(p_Text);

	// Make sure that strings are not too long.
	if (t_Length > t_MaxLetters)
		t_Length = t_MaxLetters;

	float t_Width = 1920;
	float t_Height = 1080;

	float t_CharacterSize = 32.0f;

	// A characters width on the screen
	float t_CharWidth = t_CharacterSize / t_Width;

	// A characters height on the screen
	float t_CharHeight = t_CharacterSize / t_Height;

	// cahracters texel width
	float t_TexelWidth = t_CharacterSize / 864.0f;//test

	// Rect amount of vertices
	const int t_VerticesPerLetter = 6;

	D3D11_MAPPED_SUBRESOURCE t_MapResource;
	HRESULT t_HR = p_DeviceContext->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MapResource);

	if (FAILED(t_HR))
	{
		MessageBox(nullptr, L"Could not map resource", L"Error", MB_ICONERROR | MB_OK);
		return false;
	}

	// Pointing to internal data of vertex buffer
	VertexType* t_Sprite = (VertexType*)t_MapResource.pData;

	const int indexA = static_cast<char>('A');
	const int indexZ = static_cast<char>('Z');

	for (int i = 0; i < t_Length; ++i)
	{
		float t_CurrentStartX = p_StartX + (t_CharWidth * static_cast<float>(i));
		float t_CurrentEndX = t_CurrentStartX + t_CharWidth;
		float t_CurrentEndY = p_StartY + t_CharHeight;

		t_Sprite[0].position = XMFLOAT3(t_CurrentEndX, t_CurrentEndY, 0.0f);
		t_Sprite[1].position = XMFLOAT3(t_CurrentEndX, p_StartY, 0.0f);
		t_Sprite[2].position = XMFLOAT3(t_CurrentStartX, p_StartY, 0.0f);
		t_Sprite[3].position = XMFLOAT3(t_CurrentStartX, p_StartY, 0.0f);
		t_Sprite[4].position = XMFLOAT3(t_CurrentStartX, t_CurrentEndY, 0.0f);
		t_Sprite[5].position = XMFLOAT3(t_CurrentEndX, t_CurrentEndY, 0.0f);

		int t_Vault = 0;
		int t_Letter = static_cast<char>(p_Text[i]);

		if (t_Letter < indexA || t_Letter > indexZ)
		{
			//Well this is awkward, putting an empty (space) char
			t_Vault = (indexZ - indexA) + 1;
		}
		else
		{
			// A = 0, B = 1, Z = 25, and so on
			t_Vault = (t_Letter - indexA);
		}

		float tuStart = 0.0f + (t_TexelWidth * static_cast<float>(t_Vault));
		float tuEnd = tuStart + t_TexelWidth;

		t_Sprite[0].texture = XMFLOAT2(tuEnd, 0.0f);
		t_Sprite[1].texture = XMFLOAT2(tuEnd, 1.0f);
		t_Sprite[2].texture = XMFLOAT2(tuStart, 1.0f);
		t_Sprite[3].texture = XMFLOAT2(tuStart, 1.0f);
		t_Sprite[4].texture = XMFLOAT2(tuStart, 0.0f);
		t_Sprite[5].texture = XMFLOAT2(tuEnd, 0.0f);

		t_Sprite += 6;
	}

	p_DeviceContext->Unmap(m_VertexBuffer, 0);
	p_DeviceContext->Draw(6 * t_Length, 0);


	return true;
}

void FontEngine::Render(ID3D11DeviceContext* p_DeviceContext)
{
	UINT32 t_Offset = 0;
	UINT32 t_Stride = sizeof(VertexType);

	p_DeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &t_Stride, &t_Offset);
	p_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	p_DeviceContext->PSSetSamplers(0, 1, &m_ColorMapSampler);
	
	DrawString(p_DeviceContext, "NOOOBS", -0.2f, 0.0f);
	//Render texture
	p_DeviceContext->PSSetShaderResources(0, 1, &m_Texture);
	
}

