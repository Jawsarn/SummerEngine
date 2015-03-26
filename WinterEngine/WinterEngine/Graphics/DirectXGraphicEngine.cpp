#include "DirectXGraphicEngine.h"


DirectXGraphicEngine::DirectXGraphicEngine()
{
	
}


DirectXGraphicEngine::~DirectXGraphicEngine()
{
	

}

void DirectXGraphicEngine::Release()
{
	//t_MaterialHash;
	//t_MeshHash;
	//m_MeshKeys;
	//m_MaterialKeys

	for( std::map<ID3D11ShaderResourceView*, UINT >::const_iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); it++ )
	{
		ID3D11ShaderResourceView* t_Texture = it->first;
		t_Texture->Release();
		t_Texture = nullptr;
	}
	m_TextureMap.erase( m_TextureMap.begin( ), m_TextureMap.end( ) );

	m_Device->Release();
	m_DeviceContext->Release();
	m_Device1->Release();
	m_DeviceContext1->Release();
	m_SwapChain->Release();
	//m_DriverType-
	//m_FeatureLevel
	m_RenderTargetView->Release();
	m_UnorderedAccessView->Release();

	//m_GBufferRTV[0]->Release();
	//m_GBufferRTV[1]->Release();
	//m_GBufferRTV[2]->Release();
	
	//m_GBufferSRV[0]->Release();
	//m_GBufferSRV[1]->Release();
	//m_GBufferSRV[2]->Release();

	//m_InstanceBuffer->Release();
	m_RasterizerNormal->Release();
	m_RasterizerWireframe->Release();
	m_DepthStencil->Release();
	m_DepthStencilView->Release();
	m_DepthStencilStateOn->Release();
	m_DepthStencilStateOff->Release();
	m_BlendStateOn->Release();
	m_BlendStateOff->Release();
	m_SamplerWrap->Release();
	m_SamplerClamp->Release();
	m_SamplerBorder->Release();
	m_SamplerWrapRandom->Release();

	if( m_OpaqueShaders )
	{
		m_OpaqueShaders->Release();
		delete m_OpaqueShaders;
		m_OpaqueShaders = nullptr;
	}

	if( m_DeferredComputeShader )
	{
		m_DeferredComputeShader->Release( );
		delete m_DeferredComputeShader;
		m_DeferredComputeShader = nullptr;
	}

	//m_PerFrameCBuffer->Release();
	//m_DeferredComputeCBuffer->Release();
}


