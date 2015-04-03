#include <Windows.h>
#include <list>
#include "Graphics/GraphicEngineInterface.h"
#include "Systems/RenderingSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/TransformSystem.h"
#include "Utility/Logger.h"

// this is just test at the moment, to get things started, will be sorting this when it comes important.
//global game variables
HINSTANCE	handleInstance;
HWND		m_HandleWindow;

//list with our systemss
std::list<System*> m_Systems;

//this will allow us to chose what systems we want, TODO:: solve dependencies? Renderer always need matrices.. so can't live without transform etc :)
#define SYS_RENDER
#define SYS_INPUT
#define SYS_TRANSF

//we have a define if we want to play editor or game, TODO::make this to a option in the top menu later
#define EDITOR


//functions
HRESULT InitializeWindow(_In_ HINSTANCE p_HInstance, _In_ int p_NCmdShow);
void RunEditor();
bool RunEditorFrame();
void ShutdownSystem();

void RegisterLoggers()
{
	Logger::Initialize();

	struct
	{
		std::string name;
		std::string parent;
	} loggerRegisters[] =
	{
		// NAME						PARENT
		{ "ModelImporter",			"" },
		{ "MaterialImporter",		"" },
		{ "SceneImporter",			"" },
		{ "GUIEngine",				"" },
		{ "ShaderProgram",			"" },
		{ "Texture",				"" },
		{ "Input",					"" },
		{ "Audio",					"" },
		{ "Camera",					"" },
		{ "Console",				"" },
		{ "Utility",				"" },
		{ "Serializeable",			"" },
		{ "Stream",					"" },
		{ "EntityFactory",			"" },

		{ "DirectXTransformLibrary", "" },
		{ "Debug", "" },
		{ "DirectXRenderSystem", "" },
		{ "OpenGLRenderSystem", "" },

	};

	for( auto& entry : loggerRegisters )
		Logger::RegisterLoggerType( entry.name, entry.parent );
}

void CheckForMemoryLeaks()
{
	// This will check for memory leaks
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
}

void BreakAtMemoryLeak( long value )
{
	//Insert allocation numbers here to invoke a break at that point
	_CrtSetBreakAlloc( value );
}

//testcode
#include "Entity.h"
#include "Components/RenderingComponent.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Graphics/GraphicEngineInterface.h"
#include "Matrix/MatrixLibraryInterface.h"

#include "Importers/ObjectImporter.h"
#include "Graphics/Model.h"
//main function, where the engine starts
int WINAPI wWinMain(_In_ HINSTANCE p_HInstance, _In_opt_ HINSTANCE p_HPrevInstance, _In_ LPWSTR p_LpCmdLine, _In_ int p_NCmdShow)
{
	CheckForMemoryLeaks();
	//BreakAtMemoryLeak( 346 );

	RegisterLoggers();

	UNREFERENCED_PARAMETER(p_HPrevInstance);
	UNREFERENCED_PARAMETER(p_LpCmdLine);
	
	HRESULT hr = InitializeWindow(p_HInstance, p_NCmdShow);
	if (FAILED(hr))
		return 0;

	//add systems we want from define
#ifdef SYS_RENDER
	{
		RenderingSystem* m_RS = m_RS->GetInstance();
		m_Systems.push_back(m_RS);
		//TODO:we need to initialize graphicengine here atm, because I haven't found a good solution to sending the instance stuff as a voidpointer and then later check if it's directX or not
		GraphicEngineInterface* m_Engine = m_Engine->GetInstance();
		bool t_InitializeOK = m_Engine->Initialize(m_HandleWindow, 1920, 1080);
		if (!t_InitializeOK)
			return 0;
	}
#endif
#ifdef SYS_INPUT
	InputSystem* m_IS = m_IS->GetInstance();
	m_Systems.push_back(m_IS);
#endif
#ifdef SYS_TRANSF
	MatrixLibraryInterface* m_Lib = m_Lib->GetInstance();
	m_Lib->Initialize();
	TransformSystem* m_TS = m_TS->GetInstance();
	m_Systems.push_back(m_TS);
#endif

	

	
	
	//add another function for game
#ifdef EDITOR
	//test code
	Entity* t_FirstEntity = new Entity("Orc");
	Entity* t_SecondEntity = new Entity("Orc2");
	Entity* t_CameraEntity = new Entity("Camera");

	TransformComponent* t_OrcTC = new TransformComponent();

	TransformComponent* t_Orc2TC = new TransformComponent();


	CameraComponent* t_CAMPC = new CameraComponent();
	TransformComponent* t_CAMTC = new TransformComponent();

	/*
	//create matrixes n' shit
	Matrix* t_OrcMat = new Matrix(Vec3(0,0,-10),Vec3(0,0,-1),Vec3(0,1,0));
	UINT OrcMatrix = t_OrcTC->Create(t_OrcMat);
	delete t_OrcMat;

	Matrix* t_Orc2Mat = new Matrix(Vec3(10.0f, 0, -10.0f), Vec3(0, 0, -1), Vec3(0, 1, 0));
	UINT Orc2Matrix = t_OrcTC->Create(t_Orc2Mat);
	delete t_Orc2Mat;
	*/
	
	UINT Mesh;
	UINT numbIndices = 0;
	// Loads smesh
	bool t_Worked = g_GraphicEngine->LoadModel( "", &Mesh );
	
	if (!t_Worked)
	{

	}

	// ENTITY 1
	// component has no entity yet. either send entity or send components for now compoennts..
	std::vector<RenderingComponent*> mod1RCs; // temp move to better loc
	MeshHandle handle;
	Matrix* fanMatrix = new Matrix( Vec3( 0, 5, 0 ), Vec3( 0, 0, -1 ), Vec3( 0, 1, 0 ) );
	bool status_ = g_ObjectImporter.LoadObject( "testCube.mdl", handle, mod1RCs, t_OrcTC, fanMatrix /*temp parameter mat*/ );
	
	// setting renderComponents to entity
	t_FirstEntity->AddComponent( t_OrcTC );
	RenderingComponent** comp = &mod1RCs[0];
	t_FirstEntity->AddComponents( ( Component** ) comp, mod1RCs.size() );


	// ENTITY 2
	std::vector<RenderingComponent*> mod2RC; // temp move to better loc
	MeshHandle handle2;
	Matrix* matMod = new Matrix( Vec3( -2.5f, 4, 1 ), Vec3( 0, 0, -1 ), Vec3( 0, 1, 0 ) );
	bool sta = g_ObjectImporter.LoadObject( "testSphere.mdl", handle2, mod2RC, t_Orc2TC, matMod /* todo change parameter mat*/ );

	// setting renderComponents to entity
	t_SecondEntity->AddComponent( t_Orc2TC );
	RenderingComponent** comp2 = &mod1RCs[0];
	t_SecondEntity->AddComponents( ( Component** ) comp2, mod2RC.size( ) );



	//camera
	Matrix* t_CamMat = new Matrix(Vec3(0.0f, 0.0f, 10), Vec3(0, 0, -1), Vec3(0, 1, 0));
	UINT CamMatrix = t_CAMTC->Create(t_CamMat);
	delete t_CamMat;

	// axis does not seem right? 

	FoVProjMatrix* t_CamFovMat = new FoVProjMatrix( 1920.0f / 1080.0f, 1.570796327f, 0.01f, 1000.0f );
	t_CAMPC->CreateCamera(t_CamFovMat, CamMatrix);
	delete t_CamFovMat;
	t_CAMPC->UseCamera();
	
	t_CameraEntity->AddComponent( t_CAMTC );
	t_CameraEntity->AddComponent( t_CAMPC );

	//RenderingComponent* t_ExtraTestRC = new RenderingComponent();
	//t_ExtraTestRC->Create(false, SGEngine::RenderObject(Mesh, Mat, 0, 24, OrcMatrix));

	RunEditor();
#endif

	return 0;
}

//windows callback function for messages to the windo, TODO:: atm we will take inputs from here, we might change this ?? Rawinput maybe
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		//OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HRESULT InitializeWindow(_In_ HINSTANCE p_HInstance, _In_ int p_NCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = p_HInstance;

	wcex.hIcon = LoadIcon(p_HInstance, (LPCTSTR)107);

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //IDC_ARROW IDC_NO
	//ShowCursor(false);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"SummerEngine";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)107);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	handleInstance = p_HInstance;

	RECT t_rc = { 0, 0, 1920, 1080 };
	AdjustWindowRect(&t_rc, WS_CAPTION, false);


	//AdjustWindowRect( &t_rc, WS_OVERLAPPEDWINDOW, FALSE );
	m_HandleWindow = CreateWindow(wcex.lpszClassName, wcex.lpszClassName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, t_rc.right - t_rc.left, t_rc.bottom - t_rc.top, nullptr, nullptr, p_HInstance,
		nullptr);
	if (!m_HandleWindow)
		return E_FAIL;

	ShowWindow(m_HandleWindow, p_NCmdShow);
	//ChangeDisplaySettingsA(NULL, CDS_FULLSCREEN);

	return S_OK;
}

//run the editor mode
void RunEditor()
{
	//initialize
	for each (System* t_Sys in m_Systems)
	{
		t_Sys->Start();
	}
	
	//run gameloop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		bool t_EditorContinue = RunEditorFrame();
		if (!t_EditorContinue)
			break;

		//windows peek and gives us messages from the message queue, if not used sends them forward
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	ShutdownSystem( );
}

bool RunEditorFrame()
{
	for each (System* t_Sys in m_Systems)
	{
		bool t_Continue = t_Sys->Update();
		if (!t_Continue)
			return false;
	}
	return true;
}

// TODO:: Check if using directx or opengl
#ifdef _WIN32
#include "Graphics/DirectXGraphicEngine.h"
#endif

void ShutdownSystem()
{
	for each ( System* t_Sys in m_Systems )
	{
		t_Sys->Destroy();
		delete t_Sys;
	}
	
	GraphicEngineInterface* m_Engine = m_Engine->GetInstance();
	DirectXGraphicEngine* t_DirectXEngine = ( DirectXGraphicEngine* ) m_Engine;
	t_DirectXEngine->Release();
	delete m_Engine;
}
