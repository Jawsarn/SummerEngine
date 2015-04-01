#include "DirectXGraphicEngine.h"
#include "../Utility/Logger.h"
#include "../Matrix/DirectXMatrixLibrary.h"

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

	UINT t_Strides = sizeof(XMFLOAT4X4);
	UINT t_Offsets = 0;

	m_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_DeviceContext->IASetVertexBuffers(1, 1, &m_InstanceBuffer, &t_Strides, &t_Offsets);



	//update viewmatrix
	DirectXMatrixLibrary* t_MatrixLib = (DirectXMatrixLibrary*)t_MatrixLib->GetInstance();

	UINT t_Size = m_View.size();
	for (size_t i = 0; i < t_Size; i++)
	{
		PerFrameCBuffer t_PFB;
		t_PFB.View = *t_MatrixLib->GetMatrix(m_View.at(i).camera.transformMatrixHandle);
		t_PFB.Proj = *t_MatrixLib->GetMatrix(m_View.at(i).camera.projectionMatrixHandle);
		XMMATRIX t_View = XMLoadFloat4x4(&t_PFB.View);
		XMMATRIX t_Proj = XMLoadFloat4x4(&t_PFB.Proj);
		XMMATRIX t_ViewProj = XMMatrixMultiply(t_View, t_Proj);
		XMStoreFloat4x4(&t_PFB.ViewProj, t_ViewProj);
		
		m_DeviceContext->UpdateSubresource(m_PerFrameCBuffer, 0, nullptr, &t_PFB, 0, 0);
	}
	
}

//test shit
void DirectXGraphicEngine::SetMesh(MeshHandle* p_Handle)
{
	UINT t_Strides = sizeof(SGEngine::VertexPosNormalTexTangent);
	UINT t_Offsets = 0;
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_MeshKeys[*p_Handle]->vertexBuffer, &t_Strides, &t_Offsets);
	m_DeviceContext->IASetIndexBuffer(m_MeshKeys[*p_Handle]->indexBuffer, DXGI_FORMAT_R32_UINT, t_Offsets);
}

void DirectXGraphicEngine::SetMaterial(MaterialHandle* p_Handle)
{
	m_DeviceContext->PSSetConstantBuffers(0, 1, &m_MaterialKeys.at(*p_Handle)->m_MatBuffer);
}

void DirectXGraphicEngine::SetShaderProgram(ShaderProgram* p_ShaderProgram)
{
	if (p_ShaderProgram->VertexShader != nullptr)
	{
		m_DeviceContext->VSSetShader(p_ShaderProgram->VertexShader,nullptr,0 );
	}
	if (p_ShaderProgram->InputLayout != nullptr)
	{
		m_DeviceContext->IASetInputLayout(p_ShaderProgram->InputLayout);
	}
	if (p_ShaderProgram->HullShader != nullptr)
	{
		m_DeviceContext->HSSetShader(p_ShaderProgram->HullShader, nullptr, 0);
	}
	if (p_ShaderProgram->DomainShader != nullptr)
	{
		m_DeviceContext->DSSetShader(p_ShaderProgram->DomainShader, nullptr, 0);
	}
	if (p_ShaderProgram->GeometryShader != nullptr)
	{
		m_DeviceContext->GSSetShader(p_ShaderProgram->GeometryShader, nullptr, 0);
	}
	if (p_ShaderProgram->PixelShader != nullptr)
	{
		m_DeviceContext->PSSetShader(p_ShaderProgram->PixelShader, nullptr, 0);
	}
	if (p_ShaderProgram->ComputeShader != nullptr)
	{
		m_DeviceContext->CSSetShader(p_ShaderProgram->ComputeShader, nullptr, 0);
	}

}

//Call "BeginDraw()" befor, draws nontransparent, call "ComputeDeferred()" after TODO:: test to wrap the update of matrix buffer around the creation, so we dont copy memory 2 times
void DirectXGraphicEngine::DrawOpaque(std::vector<RenderObject*> *p_RenderObects)
{
	if (!m_IsDrawing)
	{
		//TODO::ERROR MESSAGE
		return;
	}

	//set shaders
	SetShaderProgram(m_OpaqueShaders);


	//get our transform
	DirectXMatrixLibrary* t_MatrixLib = (DirectXMatrixLibrary*)t_MatrixLib->GetInstance();

	//check if any objects
	UINT t_Size = p_RenderObects->size();
	if (t_Size == 0)
		return;

	//keep track how many new matrices we have
	UINT t_NumOfMatrices = 0;

	//set first mesh, current renderobject
	UINT t_CurMeshID = p_RenderObects->at(0)->meshHandle;
	UINT t_CurMatID = p_RenderObects->at(0)->materialHandle;
	UINT t_CurStart = p_RenderObects->at(0)->startIndex;
	UINT t_CurIndexAmount = p_RenderObects->at(0)->IndexAmount;

	//the new renderobject
	UINT t_NewMeshID;
	UINT t_NewMatID;
	UINT t_NewStart;
	UINT t_NewIndexAmount;

	SetMesh(&t_CurMeshID);//TODO remove...
	SetMaterial(&t_CurMatID);

	for (UINT i = 0; i < t_Size; i++)
	{
		//check if same mesh
		t_NewMeshID = p_RenderObects->at(i)->meshHandle;
		t_NewMatID = p_RenderObects->at(i)->materialHandle;
		t_NewStart = p_RenderObects->at(i)->startIndex;
		t_NewIndexAmount = p_RenderObects->at(i)->IndexAmount;

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
						memcpy(&m_MatriceList[t_NumOfMatrices], t_MatrixLib->GetMatrix(p_RenderObects->at(i)->matrixHandle), sizeof(XMFLOAT4X4));

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
			SetMesh(&t_CurMeshID);
		}
		if (t_CurMatID == t_NewMatID)
		{
			//change if new material
			SetMaterial(&t_CurMatID);
		}
		t_CurMeshID = t_NewMeshID;
		t_CurMatID = t_NewMatID;
		t_CurStart = t_NewStart;
		t_CurIndexAmount = t_NewIndexAmount;

		memcpy(&m_MatriceList[t_NumOfMatrices], t_MatrixLib->GetMatrix(0), sizeof(XMFLOAT4X4));
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
	m_DeviceContext->DrawIndexedInstanced(t_NewIndexAmount, t_NumOfMatrices, 0, 0, 0);
}


//Computes deferrred rendering, call befor "DrawTransparent"
void DirectXGraphicEngine::ComputeDeferred()
{
	if (!m_IsDrawing)
	{
		Logger::Log("Rendering call ComputeDeferred was called before begin was called", "DirectXRenderSystem", LoggerType::MSG_ERROR);
		return;
	}

	SetShaderProgram(m_DeferredComputeShader);

	//remove render gbuffers from render target to bind it to resource
	ID3D11RenderTargetView* t_DeleteRenderTargets[3] = {nullptr, nullptr, nullptr};
	m_DeviceContext->OMSetRenderTargets(3, t_DeleteRenderTargets, m_DepthStencilView);

	//set backbuffer as unordered access
	m_DeviceContext->CSSetUnorderedAccessViews(0, 1, &m_UnorderedAccessView, nullptr);

	//set gbuffers as shader resource
	m_DeviceContext->CSSetShaderResources(1, 3, m_GBufferSRV);

	//check how many threadgroups we need
	UINT x = UINT(ceil((FLOAT)m_Width / (FLOAT)m_DeferredThreadGSize));
	UINT y = UINT(ceil((FLOAT)m_Height / (FLOAT)m_DeferredThreadGSize));

	//dispatch threads
	m_DeviceContext->Dispatch(x, y, 1);

	//set the gbuffers back as shader resources
	ID3D11ShaderResourceView* t_DeleteShaderResource[3] = { nullptr, nullptr, nullptr };
	m_DeviceContext->CSSetShaderResources(1, 3, t_DeleteShaderResource);
	m_DeviceContext->OMSetRenderTargets(3, m_GBufferRTV, m_DepthStencilView);

	
}

//Call after "ComputerDeferred()", draws transparent objects
void DirectXGraphicEngine::DrawTransparent(std::vector<RenderObject*>* p_RenderObects)
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