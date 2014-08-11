#include "ScreenManager.h"

ScreenManager* ScreenManager::m_Singelton = nullptr;
ScreenManager* ScreenManager::GetInstance()
{
	if (m_Singelton == nullptr)
	{
		m_Singelton = new ScreenManager();
	}
	return m_Singelton;
}

ScreenManager::ScreenManager()
{
	Init();
}

ScreenManager::~ScreenManager()
{
}

void ScreenManager::Release()
{
	//delete screens
	int t_ScreenSize = m_Screens.size();
	for (int i = 0; i < t_ScreenSize; i++)
	{
		if (m_Screens[i])
		{
			delete m_Screens[i];
			m_Screens[i] == nullptr;
		}
	}

	//delete vertex buffers
	int t_VertexBufferSize = m_VertexBuffers.size();
	for (int i = 0; i < t_VertexBufferSize; i++)
	{
		if (m_VertexBuffers[i])
		{
			delete(m_VertexBuffers[i]);
			m_VertexBuffers[i] = nullptr;
		}
	}
}

void ScreenManager::Init()
{
	float t_Width = 1920.0f;
	float t_Height = 1080.0f;

	CreateSprite("COL.dds", XMFLOAT2(0.8f, 0), t_Width * 0.5f, t_Height*2,XMFLOAT3(0.5f,0.5f,0.5f));
	CreateSprite("COL.dds", XMFLOAT2(0, 0.99f), t_Width * 2, 50, XMFLOAT3(0.5f,0.5f,0.5f));


	/*
	for (int i = 0; i < 1; i++)
	{
		std::string t_TextureName = "COL.dds";
		Screen* t_NewScreen = new Screen(t_TextureName);

		m_Screens.push_back(t_NewScreen);

		Renderer* t_Renderer = t_Renderer->GetInstance();

		XMFLOAT2 t_Position = XMFLOAT2(i*-1*0.1f, 0);
		float t_TextureWidth = m_Screens[i]->GetTexture()->GetWidth();
		float t_TextureHeight = m_Screens[i]->GetTexture()->GetHeight();
		
		float t_Scale = 0.01f;
		m_Screens[i]->SetScale(t_Scale);
		float t_Width = t_TextureWidth / 1920 * m_Screens[i]->GetScale();
		float t_Height = t_TextureHeight / 1080 * m_Screens[i]->GetScale();

		// 	t_Width = 1;
		// 	t_Height = 1;


		XMFLOAT3 t_LeftUp = XMFLOAT3((t_Position.x - t_Width * 0.5),
			(t_Position.y + t_Height * 0.5), 0);


		XMFLOAT3 t_LeftDown = XMFLOAT3((t_Position.x - t_Width * 0.5),
			(t_Position.y - t_Height * 0.5), 0);


		XMFLOAT3 t_RightUp = XMFLOAT3((t_Position.x + t_Width * 0.5),
			(t_Position.y + t_Height * 0.5), 0);


		XMFLOAT3 t_RightDown = XMFLOAT3((t_Position.x + t_Width * 0.5),
			(t_Position.y - t_Height * 0.5), 0);

		Sprite::Vertex2D* t_Rect = new Sprite::Vertex2D[4];

		t_Rect[2].position = t_LeftDown;
		t_Rect[2].texCoord = XMFLOAT2(0, 1);

		t_Rect[0].position = t_LeftUp;
		t_Rect[0].texCoord = XMFLOAT2(0, 0);

		t_Rect[3].position = t_RightDown;
		t_Rect[3].texCoord = XMFLOAT2(1, 1);

		t_Rect[1].position = t_RightUp;
		t_Rect[1].texCoord = XMFLOAT2(1, 0);


		//Set vertex description
		D3D11_BUFFER_DESC t_BufferDesc;
		memset(&t_BufferDesc, 0, sizeof(t_BufferDesc));
		t_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		t_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		t_BufferDesc.ByteWidth = sizeof(Sprite::Vertex2D) * 4;

		D3D11_SUBRESOURCE_DATA t_Data;
		t_Data.pSysMem = t_Rect;

		ID3D11Buffer* t_VertexBuffer = nullptr;
		t_Renderer->CreateBuffer(&t_BufferDesc, &t_Data, &t_VertexBuffer);
		m_VertexBuffers.push_back(t_VertexBuffer);

		//delete
		if (t_Rect)
		{
			delete(t_Rect);
			t_Rect = nullptr;
		}
	}
	*/
}

void ScreenManager::CreateSprite(std::string p_TextureName, XMFLOAT2 p_Position, float p_Width, float p_Height, XMFLOAT3 p_Color)
{
	Screen* t_NewScreen = new Screen(p_TextureName);

	m_Screens.push_back(t_NewScreen);

	Renderer* t_Renderer = t_Renderer->GetInstance();

	float t_Width = p_Width / 1920.0f;
	float t_Height = p_Height / 1080.0f;

	XMFLOAT3 t_LeftUp = XMFLOAT3((p_Position.x - t_Width * 0.5),
		(p_Position.y + t_Height * 0.5), 0);


	XMFLOAT3 t_LeftDown = XMFLOAT3((p_Position.x - t_Width * 0.5),
		(p_Position.y - t_Height * 0.5), 0);


	XMFLOAT3 t_RightUp = XMFLOAT3((p_Position.x + t_Width * 0.5),
		(p_Position.y + t_Height * 0.5), 0);


	XMFLOAT3 t_RightDown = XMFLOAT3((p_Position.x + t_Width * 0.5),
		(p_Position.y - t_Height * 0.5), 0);

	Sprite::Vertex2D* t_Rect = new Sprite::Vertex2D[4];

	t_Rect[2].position = t_LeftDown;
	t_Rect[2].texCoord = XMFLOAT2(0, 1);
	t_Rect[2].color = p_Color;

	t_Rect[0].position = t_LeftUp;
	t_Rect[0].texCoord = XMFLOAT2(0, 0);
	t_Rect[0].color = p_Color;

	t_Rect[3].position = t_RightDown;
	t_Rect[3].texCoord = XMFLOAT2(1, 1);
	t_Rect[3].color = p_Color;

	t_Rect[1].position = t_RightUp;
	t_Rect[1].texCoord = XMFLOAT2(1, 0);
	t_Rect[1].color = p_Color;

	//Set vertex description
	D3D11_BUFFER_DESC t_BufferDesc;
	memset(&t_BufferDesc, 0, sizeof(t_BufferDesc));
	t_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	t_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	t_BufferDesc.ByteWidth = sizeof(Sprite::Vertex2D) * 4;

	D3D11_SUBRESOURCE_DATA t_Data;
	t_Data.pSysMem = t_Rect;

	ID3D11Buffer* t_VertexBuffer = nullptr;
	t_Renderer->CreateBuffer(&t_BufferDesc, &t_Data, &t_VertexBuffer);
	m_VertexBuffers.push_back(t_VertexBuffer);

	//delete
	if (t_Rect)
	{
		delete(t_Rect);
		t_Rect = nullptr;
	}

}

void ScreenManager::MouseOver(int p_Index, int x, int y)
{
	XMFLOAT2 t_Point = XMFLOAT2(x,y);
	
	if (m_Screens[p_Index]->GetCollisionBox()->Contains(t_Point))
	{
		m_Screens[p_Index]->SetColor(XMFLOAT3(1, 0, 0));
		//m_Screens[p_Index]->SetPosition(XMFLOAT2(1,1));	//test
	}

	else
	{
		m_Screens[p_Index]->SetColor(XMFLOAT3(0, 0, 0));
	}
}

std::vector<Screen*>& ScreenManager::GetScreens()
{
	return m_Screens;
}

std::vector<ID3D11Buffer*> ScreenManager::GetVertexBuffers()
{
	return m_VertexBuffers;
}

void ScreenManager::Draw(ID3D11DeviceContext* p_DeviceContext)
{

}
