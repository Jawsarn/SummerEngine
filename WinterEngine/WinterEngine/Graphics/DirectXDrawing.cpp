#include "DirectXGraphicEngine.h"

//Needs to be called befor all other drawcalls, and ended with "EndDraw()"
void DirectXGraphicEngine::BeginDraw()
{
	if (m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		return;
	}

	//clear the backbuffer, and depthstencil buffer
	float t_Black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, t_Black);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//clear gbuffers
	for (int i = 0; i < 3; i++)
	{
		m_DeviceContext->ClearRenderTargetView(m_GBufferRTV[i], t_Black);
	}

	m_IsDrawing = true;
}

//test shit
void SetMesh()
{

}

void SetMat()
{

}

//Call "BeginDraw()" befor, draws nontransparent, call "ComputeDeferred()" after
void DirectXGraphicEngine::DrawOpaque(std::vector<RenderObject> *p_RenderObects)
{
	if (m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		return;
	}

	//check if any objects
	UINT t_Size = p_RenderObects->size();
	if (t_Size == 0)
		return;

	//the matrix vector I want to upgrade my buffer with
	std::vector<XMMATRIX> t_Matrices;
	UINT t_NumOfMatrices = 0;

	//set first mesh, current renderobject
	UINT t_CurrMeshID = p_RenderObects->at(0).meshHandle;
	UINT t_CurrMatID = p_RenderObects->at(0).materialHandle;
	UINT t_CurStart = p_RenderObects->at(0).startIndex;
	UINT t_CurEnd = p_RenderObects->at(0).endIndex;

	//the new renderobject
	UINT t_NewMeshID;
	UINT t_NewMatID;
	UINT t_NewStart;
	UINT t_NewEnd;

	void SetMesh();
	void SetMat();

	for (UINT i = 0; i < t_Size; i++)
	{
		//check if same mesh
		t_NewMeshID = p_RenderObects->at(i).meshHandle;
		t_NewMatID = p_RenderObects->at(i).materialHandle;
		t_NewStart = p_RenderObects->at(i).startIndex;
		t_NewEnd = p_RenderObects->at(i).endIndex;

		if (t_CurrMeshID == t_NewMeshID)
		{
			if (t_CurrMatID == t_NewMatID)
			{
				if (t_CurStart == t_NewStart && t_CurEnd == t_NewEnd)
				{
					//everything is same, except the world matrix
					//add matrix here
					
					//t_Matrices[t_NumOfMatrices] = p_RenderObects[i].
					t_NumOfMatrices++;
					continue;
				}
				else
				{
					//start and stop is wrong
					t_CurStart = t_NewStart;
					t_CurEnd = t_NewEnd;
				}
			}
			else
			{
				//Material, is wrong, so we set new mat,start,stop for next drawitem
				t_CurrMatID = t_NewMatID;
				t_CurStart = t_NewStart;
				t_CurEnd = t_NewEnd;
			}
		}
		else
		{
			//mesh is wrong, we set new mesh,mat,start,end for next, TODO:: Material might not be wrong , so is it wrong to add it again? Maybe...
			t_CurrMeshID = t_NewMeshID;
			t_CurrMatID = t_NewMatID;
			t_CurStart = t_NewStart;
			t_CurEnd = t_NewEnd;


			//add matrix here
			t_NumOfMatrices = 1;
		}

		//draw here
		D3D11_MAPPED_SUBRESOURCE t_MappedData;
		ZeroMemory(&t_MappedData, sizeof(D3D11_MAPPED_SUBRESOURCE));

		HRESULT hr = m_DeviceContext->Map(m_InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MappedData);
		XMMATRIX* dataView = reinterpret_cast<XMMATRIX*>(t_MappedData.pData);

		//TODO:: use memcopy instead
		int t_NumOfMatrices = t_Matrices.size();
		for (int i = 0; i < t_NumOfMatrices; i++)
		{
			dataView[i] = t_Matrices[i];
		}

		m_DeviceContext->Unmap(m_InstanceBuffer, 0);



	}


	//set mesh for current

}


//Computes deferrred rendering, call befor "DrawTransparent"
void DirectXGraphicEngine::ComputeDeferred()
{
	if (!m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		return;
	}
}

//Call after "ComputerDeferred()", draws transparent objects
void DirectXGraphicEngine::DrawTransparent(std::vector<RenderObject>* p_RenderObects)
{
	if (!m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		return;
	}
}

//Call when done drawing, needs to be started with "BeginDraw()"
void DirectXGraphicEngine::EndDraw()
{
	if (!m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		return;
	}

	m_SwapChain->Present(m_VsyncCode, 0);

	m_IsDrawing = false;
}