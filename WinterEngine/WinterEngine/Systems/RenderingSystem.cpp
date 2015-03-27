#include "RenderingSystem.h"
#include "../Graphics/GraphicEngineInterface.h"

RenderingSystem::RenderingSystem()
{
}


RenderingSystem::~RenderingSystem()
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
	//m_GraphicEngine->DrawOpaque(&m_Opaque);

	//deferred compute 
	//m_GraphicEngine->ComputeDeferred();

	//draw transparent
	//m_GraphicEngine->DrawTransparent(&m_Transparent);

	//end draw
	m_GraphicEngine->EndDraw();
	
	return true;
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
		for (size_t k = t_Size; k > i; k--)
		{
			if (m_Opaque[k].meshHandle == m_Opaque[k - 1].meshHandle) 
			{
				if (m_Opaque[k].materialHandle == m_Opaque[k - 1].materialHandle) 
				{
					if (m_Opaque[k].startIndex == m_Opaque[k - 1].startIndex) 
					{
						if (m_Opaque[k].endIndex < m_Opaque[k - 1].endIndex) //if same mesh, material, startindex, but higher endindex on left swap
						{
							//swap
							std::swap(m_Opaque[k], m_Opaque[k - 1]);
							t_Swapped = true;
						}
					}
					else if (m_Opaque[k].startIndex < m_Opaque[k - 1].startIndex) //if same material, mesh but higher startindex on left swap
					{
						//swap
						std::swap(m_Opaque[k], m_Opaque[k - 1]);
						t_Swapped = true;
					}
				}
				else if(m_Opaque[k].materialHandle < m_Opaque[k - 1].materialHandle) //if same material but higher materialindex on left swap
				{
					//swap
					std::swap(m_Opaque[k], m_Opaque[k - 1]);
					t_Swapped = true;
				}
			}
			else if (m_Opaque[k].meshHandle < m_Opaque[k - 1].meshHandle) //if material is higher on left swap
			{
				//swap if higher
				std::swap(m_Opaque[k], m_Opaque[k - 1]);
				t_Swapped = true;
			}
		}					

	}
}