#include "ShadowMap.h"


ShadowMap::ShadowMap(ID3D11Device* p_Device, UINT p_Width, UINT p_Height)
{
	m_Width = p_Width;
	m_Height = p_Height;

	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = m_Width;
	m_Viewport.Height = m_Height;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	D3D11_TEXTURE2D_DESC t_Desc;
	t_Desc.Width = m_Width;
	t_Desc.Height = m_Height;
	t_Desc.MipLevels = 1;
	t_Desc.ArraySize = 1;
	t_Desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
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
		MessageBox(nullptr, L"ShadowMapTextuerCreationError", L"Error", MB_ICONERROR | MB_OK);
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC t_DepthDesc;
	t_DepthDesc.Flags = 0;
	t_DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	t_DepthDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	t_DepthDesc.Texture2D.MipSlice = 0;
	hr = p_Device->CreateDepthStencilView(t_DepthMap, &t_DepthDesc, &m_ShadowMap);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"ShadowMapTextuerCreationError", L"Error", MB_ICONERROR | MB_OK);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC t_SRVDesc;
	t_SRVDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	t_SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	t_SRVDesc.Texture2D.MipLevels = t_Desc.MipLevels;
	t_SRVDesc.Texture2D.MostDetailedMip = 0;
	hr = p_Device->CreateShaderResourceView(t_DepthMap, &t_SRVDesc, &m_ShadowMapSRV);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"ShadowMapTextuerCreationError", L"Error", MB_ICONERROR | MB_OK);
	}
	t_DepthMap->Release();
}


ShadowMap::~ShadowMap()
{
}

void ShadowMap::PrepareDraw(ID3D11DeviceContext* p_DeviceContext)
{
	p_DeviceContext->RSSetViewports(1, &m_Viewport);

	//disable color write with null render target view
	ID3D11RenderTargetView* t_EmptyRenderTarget = { 0 };
	p_DeviceContext->OMSetRenderTargets(1, &t_EmptyRenderTarget, m_ShadowMap);

	p_DeviceContext->ClearDepthStencilView(m_ShadowMap, D3D11_CLEAR_DEPTH, 1.0f, 0);
}