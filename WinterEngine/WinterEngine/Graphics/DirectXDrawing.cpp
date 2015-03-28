#include "DirectXGraphicEngine.h"
#include "../Utility/Logger.h"
#include "../Transform/DirectXTransformLibrary.h"

//Needs to be called befor all other drawcalls, and ended with "EndDraw()"
void DirectXGraphicEngine::BeginDraw()
{
	if (m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		Logger::Log( "Rendering call Begin was called before end was called", "DirectXRenderSystem", LoggerType::MSG_ERROR );
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

//Call "BeginDraw()" befor, draws nontransparent, call "ComputeDeferred()" after TODO:: test to wrap the update of matrix buffer around the creation, so we dont copy memory 2 times
void DirectXGraphicEngine::DrawOpaque(std::vector<RenderObject> *p_RenderObects)
{
	if (m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		return;
	}

	//get our transform
	DirectXTransformLibrary* t_TransformLib = (DirectXTransformLibrary*)t_TransformLib->GetInstance();

	//check if any objects
	UINT t_Size = p_RenderObects->size();
	if (t_Size == 0)
		return;

	//keep track how many new matrices we have
	UINT t_NumOfMatrices = 0;
	UINT t_NumOfIndicies = 0;

	//set first mesh, current renderobject
	UINT t_CurMeshID = p_RenderObects->at(0).meshHandle;
	UINT t_CurMatID = p_RenderObects->at(0).materialHandle;
	UINT t_CurStart = p_RenderObects->at(0).startIndex;
	UINT t_CurIndexAmount = p_RenderObects->at(0).IndexAmount;

	//the new renderobject
	UINT t_NewMeshID;
	UINT t_NewMatID;
	UINT t_NewStart;
	UINT t_NewIndexAmount;

	void SetMesh();//TODO remove...
	void SetMat();

	for (UINT i = 0; i < t_Size; i++)
	{
		//check if same mesh
		t_NewMeshID = p_RenderObects->at(i).meshHandle;
		t_NewMatID = p_RenderObects->at(i).materialHandle;
		t_NewStart = p_RenderObects->at(i).startIndex;
		t_NewIndexAmount = p_RenderObects->at(i).IndexAmount;

		if (t_CurMeshID == t_NewMeshID)
		{
			if (t_CurMatID == t_NewMatID)
			{
				if (t_CurStart == t_NewStart && t_CurIndexAmount == t_NewIndexAmount)
				{
					//everything is same, except the world matrix
					//TODO::add matrix here
					if (t_NumOfMatrices < m_MaxNumOfInstances)
					{
						//copy memory from matrix in the library to our list
						memcpy(&m_MatriceList[t_NumOfMatrices], t_TransformLib->GetMatrix(0), sizeof(XMFLOAT4X4));

						//t_Matrices[t_NumOfMatrices] = p_RenderObects[i].
						t_NumOfMatrices++;
					}
					else
					{
						//TODO:: increase the size of the buffer oh no...
					}
					
					continue;
				}
			}
		}

		//draw here
		D3D11_MAPPED_SUBRESOURCE t_MappedData;
		ZeroMemory(&t_MappedData, sizeof(D3D11_MAPPED_SUBRESOURCE));

		//get pointer to graphic memory
		HRESULT hr = m_DeviceContext->Map(m_InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MappedData);
		XMMATRIX* dataView = reinterpret_cast<XMMATRIX*>(t_MappedData.pData);

		//copy memory to the pointer
		memcpy(&dataView[0], &m_MatriceList[0], t_NumOfMatrices* sizeof(XMFLOAT4X4));
		
		//save it
		m_DeviceContext->Unmap(m_InstanceBuffer, 0);

		//draw instances
		m_DeviceContext->DrawIndexedInstanced(t_CurIndexAmount, t_NumOfMatrices, t_CurStart, 0, 0);

		//set stuff
		if (t_CurMeshID == t_NewMeshID)
		{
			//change if new mesh
			void SetMesh();
		}
		if (t_CurMatID == t_NewMatID)
		{
			//change if new material
			void SetMat();
		}
		t_CurMeshID = t_NewMeshID;
		t_CurMatID = t_NewMatID;
		t_CurStart = t_NewStart;
		t_CurIndexAmount = t_NewIndexAmount;

		memcpy(&m_MatriceList[t_NumOfMatrices], t_TransformLib->GetMatrix(0), sizeof(XMFLOAT4X4));
		t_NumOfMatrices = 1;
	}

	//draw last
	D3D11_MAPPED_SUBRESOURCE t_MappedData;
	ZeroMemory(&t_MappedData, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//get pointer to graphic memory
	HRESULT hr = m_DeviceContext->Map(m_InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MappedData);
	XMMATRIX* dataView = reinterpret_cast<XMMATRIX*>(t_MappedData.pData);

	//copy memory to the pointer
	memcpy(&dataView[0], &m_MatriceList[0], t_NumOfMatrices* sizeof(XMFLOAT4X4));

	//save it
	m_DeviceContext->Unmap(m_InstanceBuffer, 0);

	//draw instances
	m_DeviceContext->DrawIndexedInstanced(t_NumOfIndicies, t_NumOfMatrices, 0, 0, 0);
}


//Computes deferrred rendering, call befor "DrawTransparent"
void DirectXGraphicEngine::ComputeDeferred()
{
	if (!m_IsDrawing)
	{
		Logger::Log( "Rendering call ComputeDeferred was called before begin was called", "DirectXRenderSystem", LoggerType::MSG_ERROR );
		return;
	}
}

//Call after "ComputerDeferred()", draws transparent objects
void DirectXGraphicEngine::DrawTransparent(std::vector<RenderObject>* p_RenderObects)
{
	if (!m_IsDrawing)
	{
		Logger::Log( "Rendering call DrawTransparent was called before begin was called", "DirectXRenderSystem", LoggerType::MSG_ERROR );
		return;
	}
}

//Call when done drawing, needs to be started with "BeginDraw()"
void DirectXGraphicEngine::EndDraw()
{
	if (!m_IsDrawing)
	{
		Logger::Log( "Rendering call End was called before begin was called", "DirectXRenderSystem", LoggerType::MSG_ERROR );
		return;
	}

	m_SwapChain->Present(m_VsyncCode, 0);

	m_IsDrawing = false;
}