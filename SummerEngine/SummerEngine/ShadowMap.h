#pragma once
#include <d3d11_1.h>

class ShadowMap
{
public:
	ShadowMap(ID3D11Device* p_Device, UINT p_Width, UINT p_Height);
	~ShadowMap();
	void PrepareDraw(ID3D11DeviceContext* p_DeviceContext);

	ID3D11ShaderResourceView* GetResourceView();
	UINT GetWidth();
	UINT GetHeight();
private:
	void CreateRenderTarget(ID3D11Device* p_Device, float p_Width, float p_Height);

	UINT m_Width;
	UINT m_Height;
	ID3D11ShaderResourceView* m_ShadowMapSRV;
	ID3D11DepthStencilView* m_ShadowMap;
	D3D11_VIEWPORT m_Viewport;
	ID3D11RenderTargetView* m_DebugRenderTarget;
	ID3D11ShaderResourceView* m_ShadowRenderTargetSRV;
};

