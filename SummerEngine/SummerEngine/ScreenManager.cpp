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

void ScreenManager::Init()
{
	std::string t_TextureName = "COL.dds";
	Screen* t_NewScreen = new Screen(t_TextureName);
	
	m_Screens.push_back(t_NewScreen);
	m_Screens[0]->SetPosition(XMFLOAT2(0.25f, 0.25f));
}



void ScreenManager::Update(int x, int y)
{
	XMFLOAT2 t_Point = XMFLOAT2(x,y);
	

	if (m_Screens[0]->GetCollisionBox()->Contains(t_Point))
	{
		m_Screens[0]->SetColor(XMFLOAT4(1,0,0,0));
	}

	else
	{
		m_Screens[0]->SetColor(XMFLOAT4(0, 0, 0, 0));
	}
	
	
}

void ScreenManager::Draw()
{
	
}

std::vector<Screen*>& ScreenManager::GetScreen()
{
	return m_Screens;
}

