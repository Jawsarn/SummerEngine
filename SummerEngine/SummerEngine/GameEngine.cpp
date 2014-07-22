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

struct TestVector
{
	float a;
	float b;
	TestVector()
	{
		a = 0;
		b = 0;
	}
	TestVector(float p_a, float p_b)
	{
		a = p_a;
		b = p_b;
	}
};
#include "LoadObj.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

bool GameEngine::Start(UINT p_Width, UINT p_Height, HWND p_HandleWindow)
{
	Renderer* t_RendererStartup = t_RendererStartup->GetInstance();
	t_RendererStartup->Initialize(1920, 1080, p_HandleWindow);

	m_RenderingSystem = m_RenderingSystem->GetInstance();
	m_RenderingSystem->Start();

	//shouldn't be here untill later maybe? ... depends
	m_EntityTest = new Entity();
	CameraComponent* t_NewComponent = new CameraComponent();
	t_NewComponent->SetLens(XM_PIDIV4, 1920/1080, 0.5f, 10000);
	TransformComponent* t_NewTransform = new TransformComponent();
	
	t_NewTransform->SetTranslation(XMFLOAT3(0,0,0));
	t_NewTransform->SetRotation(XMFLOAT3(0, 0, 0));
	t_NewTransform->SetScale(XMFLOAT3(1, 1, 1));

	m_EntityTest->AddComponent(t_NewComponent);
	m_EntityTest->SetTransformComponent(t_NewTransform);
	

	int working = 0;


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