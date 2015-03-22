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
			m_Screens[i] = nullptr;
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

	{
		m_FontRenderer = nullptr;
		m_FontRenderer = new FontEngine();
		m_FontRenderer->LoadContent();

		//Fonts
			//Visible All the Time
		m_FontRenderer->CreateText("FILE", -0.99f, 0.965f);


		m_FontRenderer->CreateText("PROPERTIES", 0.72f, 0.1f);
		m_FontRenderer->CreateText("OUTLINER", 0.72f, 0.91f);
	}
	
	
	//Outliner
	UISprites* t_OutLiner = new UISprites();
	t_OutLiner->textureName = "";
	t_OutLiner->position = XMFLOAT2(0.8f,0.55f);
	t_OutLiner->width = t_Width * 0.5f;
	t_OutLiner->height = t_Height * 0.82f;
	t_OutLiner->color = XMFLOAT3(0.15f, 0.15f, 0.15f);
	
	//properties
	UISprites* t_Properties = new UISprites();
	t_Properties->textureName = "";
	t_Properties->position = XMFLOAT2(0.8f, -0.25f);
	t_Properties->width = t_Width * 0.5f;
	t_Properties->height = t_Height * 1.5f;
	t_Properties->color = XMFLOAT3(0.2f, 0.2f, 0.2f);

	//Info
	UISprites* t_Info = new UISprites();
	t_Properties->textureName = "";
	t_Info->width = t_Width * 6;
	t_Info->height = t_Height * 0.06f;
	t_Info->position = XMFLOAT2(0, 0.99f);
	t_Info->color = XMFLOAT3(0.2f, 0.2f, 0.2f);

		//Visible
	CreateSprite(t_Info);


	CreateSprite(t_OutLiner);
	CreateSprite(t_Properties);
	//CreateSprite("", XMFLOAT2(0.8f, 0), t_Width , t_Height * 2,XMFLOAT3(0.5f,0.0f,0.0f));

	
	//CreateSprite("COL.dds", XMFLOAT2(0, 0.99f), t_Width * 2, 50, XMFLOAT3(0.5f,0.5f,0.5f));
	//CreateSprite("COL.dds", XMFLOAT2(0.0f, 0.0f), t_Width , t_Height, XMFLOAT3(1.0f, 0.5f, 0.5f));

	//ResourceManager* t_ResourceManager = t_ResourceManager->GetInstance();
	//m_Texture = (Texture*)t_ResourceManager->Create("COL.dds");
}

void ScreenManager::CreateSprite(std::string p_TextureName, XMFLOAT2 p_Position, float p_Width, float p_Height, XMFLOAT3 p_Color)
{
	UISprites* t_Sprite = nullptr;
	t_Sprite = new UISprites();
	t_Sprite->textureName = p_TextureName;
	t_Sprite->position =p_Position;
	t_Sprite->width = p_Width;
	t_Sprite->height = p_Height;
	t_Sprite->color = p_Color;

	CreateSprite(t_Sprite);
}

void ScreenManager::CreateSprite(UISprites* p_Sprite)
{
	std::string t_DefaultTexture = "default.dds";
	if (p_Sprite->textureName.compare("") == 0)
	{
		Screen* t_NewScreen = new Screen(t_DefaultTexture);
		m_Screens.push_back(t_NewScreen);
	}

	else
	{
		Screen* t_NewScreen = new Screen(p_Sprite->textureName);
		m_Screens.push_back(t_NewScreen);
	}


	Renderer* t_Renderer = t_Renderer->GetInstance();

	float t_Width = p_Sprite->width / 1920.0f;
	float t_Height = p_Sprite->height / 1080.0f;

	int t_ScreenSize = m_Screens.size();
	//m_Screens[t_ScreenSize - 1]->SetWidth(t_Width);
	//m_Screens[t_ScreenSize - 1]->SetHeight(t_Height);

	XMFLOAT3 t_LeftUp = XMFLOAT3((p_Sprite->position.x - t_Width * 0.5f),
		(p_Sprite->position.y + t_Height * 0.5f), 0);


	XMFLOAT3 t_LeftDown = XMFLOAT3((p_Sprite->position.x - t_Width * 0.5f),
		(p_Sprite->position.y - t_Height * 0.5f), 0);


	XMFLOAT3 t_RightUp = XMFLOAT3((p_Sprite->position.x + t_Width * 0.5f),
		(p_Sprite->position.y + t_Height * 0.5f), 0);


	XMFLOAT3 t_RightDown = XMFLOAT3((p_Sprite->position.x + t_Width * 0.5f),
		(p_Sprite->position.y - t_Height * 0.5f), 0);

	Sprite::Vertex2D* t_Rect = new Sprite::Vertex2D[4];

	t_Rect[2].position = t_LeftDown;
	t_Rect[2].texCoord = XMFLOAT2(0, 1);
	t_Rect[2].color = p_Sprite->color;

	t_Rect[0].position = t_LeftUp;
	t_Rect[0].texCoord = XMFLOAT2(0, 0);
	t_Rect[0].color = p_Sprite->color;

	t_Rect[3].position = t_RightDown;
	t_Rect[3].texCoord = XMFLOAT2(1, 1);
	t_Rect[3].color = p_Sprite->color;

	t_Rect[1].position = t_RightUp;
	t_Rect[1].texCoord = XMFLOAT2(1, 0);
	t_Rect[1].color = p_Sprite->color;

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


	//Constant Buffer
	m_CColorBuffer = nullptr;
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(ScreenColorBufferStruct);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;
	cbbd.StructureByteStride = 0;

	t_Renderer->CreateBuffer(&cbbd, nullptr, &m_CColorBuffer);


	//delete the rectangle ( vertices )
	if (t_Rect)
	{
		delete(t_Rect);
		t_Rect = nullptr;
	}
	//delete the sprite (name, pos,width,height,color)

	if (p_Sprite)
	{
		delete(p_Sprite);
		p_Sprite = nullptr;
	}

}

void ScreenManager::MouseOver(int p_Index, const float x, const float y)
{
	XMFLOAT2 t_Point = XMFLOAT2(x,y);
	int t_Size =  m_Screens.size();


	if (t_Size > 0)
	{
		//t_Point.x /= 1920;
		//t_Point.y /= 1080;
		
		if (m_Screens[p_Index]->GetCollisionBox()->Contains(t_Point))
		{

			//t_Width * 0.5f;
			//t_OutLiner->height = t_Height * 0.8f;	//PROPERTIES

			m_CbScreenColor.color = XMFLOAT3(0, 1, 0);
			m_Screens[p_Index]->SetColor(XMFLOAT3(0, 1, 0));
			
			//m_Screens[p_Index]->SetPosition(XMFLOAT2(1,1));	//test
		}

		else
		{
			m_Screens[p_Index]->SetColor(XMFLOAT3(0, 0, 0));
			m_CbScreenColor.color = XMFLOAT3(0, 0, 0);
		}
	}
}

void ScreenManager::Update(ID3D11DeviceContext* p_DeviceContext)
{
	int t_ScreenSize = m_Screens.size();
	//if (GetAsyncKeyState(VK_SPACE) & 0x80000)
	if (GetAsyncKeyState('N') & 0x80000)
	{
		//SCREENS
		//Jumping over the first screen because it's always going to be there (info)
		for (int i = 1; i < t_ScreenSize; i++)
		{
			m_Screens[i]->SetIsRendered(false);
		}

		//FONT
		int t_FontCount = m_FontRenderer->GetFontList()->size();
		for (int i = 1; i < t_FontCount; i++)
		{
			m_FontRenderer->GetFont(i)->isRender = false;
		}
		
	}

	else if (GetAsyncKeyState('1') & 0x80000)
	{
		//SCREENS
		//Jumping over the first screen because it's always going to be there (info)
		for (int i = 1; i < t_ScreenSize; i++)
		{
			m_Screens[i]->SetIsRendered(true);
		}

		//FONT
		int t_FontCount = m_FontRenderer->GetFontList()->size();
		for (int i = 1; i < t_FontCount; i++)
		{
			m_FontRenderer->GetFont(i)->isRender = true;
		}
	}
	//m_FontRenderer->Render(p_DeviceContext);
	
	//ID3D11ShaderResourceView* t_View = m_Texture->GetTextureView();
	//p_DeviceContext->PSSetShaderResources(10, 1, &t_View);
	//p_DeviceContext->UpdateSubresource(m_CColorBuffer, 0, nullptr, &cbScreenColor, 0, 0);
	//p_DeviceContext->PSSetConstantBuffers(3, 1, &m_CColorBuffer);
}


std::vector<Screen*>& ScreenManager::GetScreens()
{
	return m_Screens;
}

std::vector<ID3D11Buffer*> ScreenManager::GetVertexBuffers()
{
	return m_VertexBuffers;
}

Screen* ScreenManager::GetScreen(int p_Index)
{
	return m_Screens[p_Index];
}

void ScreenManager::RenderFont(ID3D11DeviceContext* p_DeviceContext)
{
	m_FontRenderer->Render(p_DeviceContext);
}

