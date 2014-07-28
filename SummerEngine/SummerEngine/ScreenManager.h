#pragma once
#include "Screen.h"
#include <vector>

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();
	void Update(float p_DeltaTime);
	void Draw();
	std::vector<Screen*>& GetScreen();

private:
	std::vector<Screen*> m_Screens;

};

