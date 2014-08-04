#pragma once
#include "Screen.h"
#include <vector>
#include "Renderer.h"

class ScreenManager
{

public:
	static ScreenManager* GetInstance();
	void Release();

	void Init();
	void MouseOver(int p_Index, int x, int y);

	std::vector<Screen*>& GetScreens();
	std::vector<ID3D11Buffer*> GetVertexBuffers();
	//void CreateSprite(std::string p_Name, XMFLOAT2 p_Position, float p_Width, float p_Height );
	void Draw(ID3D11DeviceContext* p_DeviceContext);

private:
	ScreenManager();
	~ScreenManager();
	static ScreenManager* m_Singelton;

	std::vector<Screen*> m_Screens;
	std::vector<ID3D11Buffer*> m_VertexBuffers;

};

