#pragma once
#include "Screen.h"
#include <vector>
#include "Renderer.h"

class ScreenManager
{

public:
	static ScreenManager* GetInstance();

	void Init();
	void Update(int x , int y);

	std::vector<Screen*>& GetScreen();
	ID3D11Buffer* GetVertexBuffer();

private:
	ScreenManager();
	~ScreenManager();
	static ScreenManager* m_Singelton;

	std::vector<Screen*> m_Screens;
	ID3D11Buffer* m_VertexBuffer;

};

