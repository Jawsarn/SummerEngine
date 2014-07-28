#include "ScreenManager.h"


ScreenManager::ScreenManager()
{
}


ScreenManager::~ScreenManager()
{
}



void ScreenManager::Update(float p_DeltaTime)
{

}

void ScreenManager::Draw()
{

}

std::vector<Screen*>& ScreenManager::GetScreen()
{
	return m_Screens;
}