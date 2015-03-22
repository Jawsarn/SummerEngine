#include "ShadowMap.h"
#include <DirectXColors.h>
#include "Logger.h"

ShadowMap::ShadowMap(ID3D11Device* p_Device, UINT p_Width, UINT p_Height)
{
	m_Width = p_Width;
	m_Height = p_Height;

	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = static_cast<FLOAT>( m_Width );
	m_Viewport.Height = static_cast<FLOAT>( m_Height );
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	D3D11_TEXTURE2D_DESC t_Desc;
	t_Desc.Width = m_Width;
	t_Desc.Height = m_Height;
	t_Desc.MipLevels = 1;
	t_Desc.ArraySize = 1;
	t_Desc.Format = DXGI_FORMAT_R24G8_TYPELESS; //DXGI_FORMAT_R24G8_TYPELESS
	t_Desc.SampleDesc.Count = 1;
	t_Desc.SampleDesc.Quality = 0;
	t_Desc.Usage = D3D11_USAGE_DEFAULT;
	t_Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	t_Desc.CPUAccessFlags = 0;
	t_Desc.MiscFlags = 0;

	ID3D11Texture2D* t_DepthMap = 0;
	HRESULT hr = S_OK;
	hr = p_Device->CreateTexture2D(&t_Desc, 0, &t_DepthMap);
	if (FAILED(hr))
	{
		//MessageBox(nullptr, L"ShadowMapTextuerCreationError", L"Error", MB_ICONERROR | MB_OK);
		Logger::Log( "ShadowMapTextuerCreationError", "RenderSystem", LoggerType::MSG_ERROR );
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC t_DepthDesc;
	t_DepthDesc.Flags = 0;
	t_DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	t_DepthDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	t_DepthDesc.Texture2D.MipSlice = 0;
	hr = p_Device->CreateDepthStencilView(t_DepthMap, &t_DepthDesc, &m_ShadowMap);
	if (FAILED(hr))
	{
		//MessageBox(nullptr, L"ShadowMapTextuerCreationError", L"Error", MB_ICONERROR | MB_OK);
		Logger::Log( "ShadowMapTextuerCreationError", "RenderSystem", LoggerType::MSG_ERROR );
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC t_SRVDesc;
	t_SRVDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	t_SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	t_SRVDesc.Texture2D.MipLevels = t_Desc.MipLevels;
	t_SRVDesc.Texture2D.MostDetailedMip = 0;
	hr = p_Device->CreateShaderResourceView(t_DepthMap, &t_SRVDesc, &m_ShadowMapSRV);
	if (FAILED(hr))
	{
		//MessageBox(nullptr, L"ShadowMapTextuerCreationError", L"Error", MB_ICONERROR | MB_OK);
		Logger::Log( "ShadowMapTextuerCreationError", "RenderSystem", LoggerType::MSG_ERROR );
	}
	t_DepthMap->Release();
	
	CreateRenderTarget(p_Device, (float)p_Width, (float)p_Height);
}

void ShadowMap::CreateRenderTarget(ID3D11Device* p_Device, float p_Width, float p_Height)
{
	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = static_cast<UINT> ( p_Width );
	desc.Height = static_cast<UINT> ( p_Height );
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32_FLOAT; //changed from format DXGI_FORMAT_R16G16B16A16_UNORM
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;


	D3D11_SHADER_RESOURCE_VIEW_DESC t_SrvDesc;
	t_SrvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	t_SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	t_SrvDesc.Texture2D.MostDetailedMip = 0;
	t_SrvDesc.Texture2D.MipLevels = 1;



	ID3D11Texture2D* t_Texture = 0;

	hr = p_Device->CreateTexture2D(&desc, 0, &t_Texture);
	if (FAILED(hr))
		return;

	hr = p_Device->CreateShaderResourceView(t_Texture, &t_SrvDesc, &m_ShadowRenderTargetSRV);
	if (FAILED(hr))
		return;


	hr = p_Device->CreateRenderTargetView(t_Texture, nullptr, &m_DebugRenderTarget);
	if (FAILED(hr))
		return;


	t_Texture->Release();
}

ShadowMap::~ShadowMap()
{
}

void ShadowMap::PrepareDraw(ID3D11DeviceContext* p_DeviceContext)
{
	p_DeviceContext->RSSetViewports(1, &m_Viewport);

	//disable color write with null render target view
	//ID3D11RenderTargetView* t_EmptyRenderTarget = { 0 };
	p_DeviceContext->OMSetRenderTargets(1, &m_DebugRenderTarget, m_ShadowMap);

	p_DeviceContext->ClearDepthStencilView(m_ShadowMap, D3D11_CLEAR_DEPTH, 1.0f, 0);
	p_DeviceContext->ClearRenderTargetView(m_DebugRenderTarget, DirectX::Colors::Black);

}

ID3D11ShaderResourceView* ShadowMap::GetResourceView()
{
	return m_ShadowMapSRV;
}

UINT ShadowMap::GetWidth()
{
	return m_Width;
}

UINT ShadowMap::GetHeight()
{
	return m_Height;
}