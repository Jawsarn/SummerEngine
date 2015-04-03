#include "RenderingSystem.h"
#include "../Graphics/GraphicEngineInterface.h"
#include "../Components/RenderingComponent.h"

RenderingSystem* RenderingSystem::m_Singleton = nullptr;

RenderingSystem* RenderingSystem::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new RenderingSystem();
	}

	return m_Singleton;
}

RenderingSystem::RenderingSystem()
{
}


RenderingSystem::~RenderingSystem()
{
}

//used after sleep as constructor
void RenderingSystem::Awake()
{

}

//starting the system
void RenderingSystem::Start()
{

}

//pausing the system
void RenderingSystem::Sleep()
{

}



//updating the system, called from gameloop
bool RenderingSystem::Update()
{
	//get graphicengine
	GraphicEngineInterface* m_GraphicEngine = m_GraphicEngine->GetInstance();

	//sort our drawing things, 
	SortComponents();

	//begin draw
	m_GraphicEngine->BeginDraw();

	//start drawing non-transparent stuff
	m_GraphicEngine->DrawOpaque(&m_Opaque);

	//deferred compute 
	m_GraphicEngine->ComputeDeferred();

	//draw transparent
	//m_GraphicEngine->DrawTransparent(&m_Transparent);

	//end draw
	m_GraphicEngine->EndDraw();
	
	return true;
}

//dealloc the system
void RenderingSystem::Destroy()
{

}

//TODO:: check if the object for this key already exist
unsigned int RenderingSystem::AddObjects( RenderingComponent* p_Component )
{
	std::vector<RenderObject*> objs = p_Component->GetRenderObjects();

	for( int i = 0; i < objs.size(); i++ )
	{
		RenderObject* t_Object = objs[i];

		std::hash<RenderingComponent*> t_Hasher;
		unsigned int o_Key = t_Hasher( p_Component );
		t_Object->componentHandle = o_Key;
		
		// todo create Get material function and check if transparent
		if( t_Object->materialHandle == 1 /*is transparent */ )
		{
			//////m_Transparent.push_back(t_NewObject);
		}

		else
		{
			m_Opaque.push_back( t_Object );
		}
	}

	// do we even need to return something here?
	return 1;//o_Key;
}

unsigned int RenderingSystem::AddCamera(MatrixHandle p_Transform, MatrixHandle p_Projection, CameraComponent* p_Component)
{
	SGEngine::Camera t_NewCamera = SGEngine::Camera();
	t_NewCamera.transformMatrixHandle = p_Transform;
	t_NewCamera.projectionMatrixHandle = p_Projection;

	std::hash<CameraComponent*> t_Hash;

	SGEngine::ComponentHandle t_Key = t_Hash(p_Component);

	t_NewCamera.componentHandle = t_Key;
	m_Cameras.push_back(t_NewCamera);

	return t_Key;
}

void RenderingSystem::UseCamera(SGEngine::ComponentHandle p_CameraHandle)
{
	//get graphicengine
	GraphicEngineInterface* m_GraphicEngine = m_GraphicEngine->GetInstance();

	for each (SGEngine::Camera t_Cam in m_Cameras)
	{
		if (t_Cam.componentHandle == p_CameraHandle)
		{
			//TODO::remove hardcoding
			m_GraphicEngine->UseCamera(t_Cam,0);
		}
	}
}

//bubble sort sort the list, this is fine atm, since not much change will happen and bubble sort is speed n on sorted lists, which it mostly will be
void RenderingSystem::SortComponents()
{
	UINT t_Size = m_Opaque.size();
	bool t_Swapped = true;

	//if we are done, or didnt swap anything ,we're done sorting
	for (size_t i = 0; i < t_Size && t_Swapped; i++)
	{
		t_Swapped = false;
		for (size_t k = t_Size - 1; k > i; k--)
		{
			if (m_Opaque[k]->meshHandle == m_Opaque[k - 1]->meshHandle)
			{
				if (m_Opaque[k]->materialHandle == m_Opaque[k - 1]->materialHandle)
				{
					if (m_Opaque[k]->startIndex == m_Opaque[k - 1]->startIndex) 
					{
						if (m_Opaque[k]->IndexAmount < m_Opaque[k - 1]->IndexAmount) //if same mesh, material, startindex, but higher endindex on left swap
						{
							//swap
							std::swap(m_Opaque[k], m_Opaque[k - 1]);
							t_Swapped = true;
						}
					}
					else if (m_Opaque[k]->startIndex < m_Opaque[k - 1]->startIndex) //if same material, mesh but higher startindex on left swap
					{
						//swap
						std::swap(m_Opaque[k], m_Opaque[k - 1]);
						t_Swapped = true;
					}
				}
				else if(m_Opaque[k]->materialHandle < m_Opaque[k - 1]->materialHandle) //if same material but higher materialindex on left swap
				{
					//swap
					std::swap(m_Opaque[k], m_Opaque[k - 1]);
					t_Swapped = true;
				}
			}
			else if (m_Opaque[k]->meshHandle < m_Opaque[k - 1]->meshHandle) //if material is higher on left swap
			{
				//swap if higher
				std::swap(m_Opaque[k], m_Opaque[k - 1]);
				t_Swapped = true;
			}
		}					

	}
}