#pragma once
#include "Screen.h"
#include <vector>
#include "Renderer.h"
#include "ResourceManager.h"
//#include "Texture.h"

class ScreenManager
{
	
public:
	static ScreenManager* GetInstance();
	void Release();

	struct RenderSprites
	{
		std::string textureName;
		XMFLOAT2 position;
		float width;
		float height;
		XMFLOAT3 color;
	};

	void Init();
	void MouseOver(int p_Index, int x, int y);

	std::vector<Screen*>& GetScreens();
	std::vector<ID3D11Buffer*> GetVertexBuffers();
	void CreateSprite(RenderSprites* p_Sprite);
	void Update(ID3D11DeviceContext* p_DeviceContext);
	
	

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
	}cbScreenColor;
	ID3D11Buffer* m_CColorBuffer;
};

