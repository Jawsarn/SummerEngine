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
	void Draw();
	std::vector<Screen*>& GetScreen();
	

private:
	ScreenManager();
	~ScreenManager();
	static ScreenManager* m_Singelton;

	std::vector<Screen*> m_Screens;
	

};

