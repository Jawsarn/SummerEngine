#pragma once
#include "Screen.h"
#include <vector>
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "FontEngine.h"

class FontEngine;

class ScreenManager
{
	
public:
	static ScreenManager* GetInstance();
	void Release();

	struct UISprites
	{
		std::string textureName;
		XMFLOAT2 position;
		float width;
		float height;
		XMFLOAT3 color;
	};

	void Init();
	void MouseOver(int p_Index, const float x, const float y);

	std::vector<Screen*>& GetScreens();
	Screen* GetScreen(int p_Index);
	std::vector<ID3D11Buffer*> GetVertexBuffers();
	void CreateSprite(UISprites* p_Sprite);
	void CreateSprite(std::string p_TextureName, XMFLOAT2 p_Position, float p_Width, float p_Height, XMFLOAT3 p_Color);
	void Update(ID3D11DeviceContext* p_DeviceContext);
	void RenderFont(ID3D11DeviceContext* p_DeviceContext);
	

private:
	ScreenManager();
	~ScreenManager();
	static ScreenManager* m_Singelton;

	std::vector<Screen*> m_Screens;
	std::vector<ID3D11Buffer*> m_VertexBuffers;
	//Texture* m_Texture;

	struct ScreenColorBufferStruct
	{
		XMFLOAT3 color;
		float pad1;
	}m_CbScreenColor;
	ID3D11Buffer* m_CColorBuffer;

	FontEngine* m_FontRenderer;

};

