#include "GameEngine.h"


GameEngine* GameEngine::m_Singleton = nullptr;

GameEngine* GameEngine::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new GameEngine();
	}

	return m_Singleton;
}

GameEngine::GameEngine()
{
	m_DeltaTime = new DOUBLE();
	m_GameTime = new DOUBLE();
	m_PrevTime = new ULONGLONG();

	*m_DeltaTime = 0;
	*m_GameTime = 0;
	*m_PrevTime = 0;
	m_RenderingSystem = nullptr;
}


GameEngine::~GameEngine()
{
}
#include "RenderComponent.h"
#include "ExtensibleGameFactory.h"
#include "StreamFile.h"
#include "Stream.h"


bool GameEngine::Start(UINT p_Width, UINT p_Height, HWND p_HandleWindow)
{
	Renderer* t_RendererStartup = t_RendererStartup->GetInstance();
	t_RendererStartup->Initialize(1920, 1080, p_HandleWindow);

	m_RenderingSystem = m_RenderingSystem->GetInstance();
	m_RenderingSystem->Start();


	//test IO
	StreamFile t_tes = StreamFile();
	t_tes.OpenFileWrite("TheFileSavingIsWorking.working");
	
	WriteInt(t_tes, 1337);
	WriteString(t_tes,"This seems to be working");
	WriteInt(t_tes, 666);
	WriteBool(t_tes, true);
	WriteString(t_tes, "Yep working");

	t_tes.Close();


	t_tes.OpenFileRead("TheFileSavingIsWorking.working");
	int a = ReadInt(t_tes);
	std::string b = ReadString(t_tes);
	int c = ReadInt(t_tes);
	bool d = ReadBool(t_tes);
	std::string e = ReadString(t_tes);
	t_tes.Close();



	return true;
}



void GameEngine::Destroy()
{

}

void GameEngine::Update()
{
	UpdateTime();
	//GetInput();
	//GetNetworkMessages();
	//SimulateWorld();
	//CollisionStep();
	//UpdateObjects();
	RenderWorld();
	//MiscTasks();
}

void GameEngine::UpdateTime()
{
	ULONGLONG timeCur = GetTickCount64();
	if (*m_PrevTime == 0)
		*m_PrevTime = timeCur;
	*m_DeltaTime = (timeCur - *m_PrevTime) / 1000.0f;
	*m_GameTime += *m_DeltaTime;
	*m_PrevTime = timeCur;
}

void GameEngine::GetInput()
{

}

void GameEngine::GetNetworkMessages()
{

}

void GameEngine::SimulateWorld()
{

}

void GameEngine::CollisionStep()
{

}

void GameEngine::UpdateObjects()
{

}

void GameEngine::RenderWorld()
{
	m_RenderingSystem->Update();
}

void GameEngine::MiscTasks()
{

}