#include "Renderer.h"
#include <DirectXColors.h>
#include "RenderComponent.h"
#include "TransformComponent.h"


Renderer* Renderer::m_Singleton = nullptr;

Renderer* Renderer::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new Renderer();
	}
	return m_Singleton;
}

Renderer::Renderer()
{
	m_Height = new UINT();
	m_Width = new UINT();
	*m_Height = 0;
	*m_Width = 0;
	m_IsRendering = false;
}


Renderer::~Renderer()
{
}

bool Renderer::Initialize(UINT p_Width, UINT p_Height, HWND p_HandleWindow) //fix the load if somethings crash ni middle to unload everything
{
	HRESULT hr = S_OK;

	*m_Height = p_Height;
	*m_Width = p_Width;

	hr = InitializeDriverAndVersion(p_HandleWindow);
	if( FAILED( hr ) )
		return false;

	hr = InitializeRenderTargetView();
	if (FAILED(hr))
		return false;

	InitializeViewports();

	hr = InitializeRasterizers();
	if (FAILED(hr))
		return false;

	hr = InitializeDeptpAndStates();
	if (FAILED(hr))
		return false;

	hr = InitializeBlendAndStates();
	if (FAILED(hr))
		return false;

	hr = InitializeShaders();
	if (FAILED(hr))
		return false;

	hr = InitializeConstantBuffers();
	if (FAILED(hr))
		return false;

	hr = InitializeGBuffers();
	if (FAILED(hr))
		return false;

	hr = InitializeSamplerState();
	if (FAILED(hr))
		return false;



	return true;
}


HRESULT Renderer::InitializeDriverAndVersion(HWND p_HandleWindow)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = *m_Width;
	sd.BufferDesc.Height = *m_Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS; //fixed for deferred rendering, set flag for input if want to put into a shader as well I guess
	sd.OutputWindow = p_HandleWindow;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			m_DriverType,
			nullptr,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&sd,
			&m_SwapChain,
			&m_Device,
			&m_FeatureLevel,
			&m_DeviceContext);

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,
				m_DriverType,
				nullptr,
				createDeviceFlags,
				&featureLevels[1],
				numFeatureLevels - 1,
				D3D11_SDK_VERSION, &sd,
				&m_SwapChain,
				&m_Device,
				&m_FeatureLevel,
				&m_DeviceContext);
		}

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Obtain the Direct3D 11.1 versions if available
	hr = m_Device->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&m_Device1));
	if (SUCCEEDED(hr))
	{
		(void)m_DeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_DeviceContext1));
	}
	return hr;
}

HRESULT Renderer::InitializeRenderTargetView()
{
	HRESULT hr = S_OK;

	ID3D11Texture2D* t_BackBuffer = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&t_BackBuffer);
	if (FAILED(hr))
		return hr;

	hr = m_Device->CreateRenderTargetView(t_BackBuffer, nullptr, &m_RenderTargetView);
	if (FAILED(hr))
		return hr;

	hr = m_Device->CreateUnorderedAccessView(t_BackBuffer, nullptr, &m_BackBufferUAV);
	if (FAILED(hr))
		return hr;

	t_BackBuffer->Release();


	return hr;
}

void Renderer::InitializeViewports()
{
	D3D11_VIEWPORT vp;

	vp.Width = (FLOAT)*m_Width;
	vp.Height = (FLOAT)*m_Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_DeviceContext->RSSetViewports(1, &vp);
}

HRESULT Renderer::InitializeRasterizers()
{
	HRESULT hr = S_OK;
	D3D11_RASTERIZER_DESC desc;

	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_NONE;  //TODO D3D11_CULL_BACK D3D11_CULL_NONE
	desc.FrontCounterClockwise = false;
	desc.DepthBias = 0;
	desc.SlopeScaledDepthBias = 0.0f;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = true; //changed
	desc.ScissorEnable = false;
	desc.MultisampleEnable = false;
	desc.AntialiasedLineEnable = false;

	hr = m_Device->CreateRasterizerState(&desc, &m_RasterizerStateNormal);
	if (FAILED(hr))
		return hr;

	desc.FillMode = D3D11_FILL_WIREFRAME;

	hr = m_Device->CreateRasterizerState(&desc, &m_RasterizerStateWireframe);
	if (FAILED(hr))
		return hr;


	m_DeviceContext->RSSetState(m_RasterizerStateNormal);

	return hr;
}

HRESULT Renderer::InitializeDeptpAndStates()
{
	HRESULT hr = S_OK;

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = *m_Width;
	descDepth.Height = *m_Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	hr = m_Device->CreateTexture2D(&descDepth, nullptr, &m_DepthStencil);
	if (FAILED(hr))
		return hr;

	D3D11_DEPTH_STENCIL_VIEW_DESC t_DescDSV;
	ZeroMemory(&t_DescDSV, sizeof(t_DescDSV));
	t_DescDSV.Format = descDepth.Format;
	t_DescDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	t_DescDSV.Texture2D.MipSlice = 0;
	hr = m_Device->CreateDepthStencilView(m_DepthStencil, &t_DescDSV, &m_DepthStencilView);
	if (FAILED(hr))
		return hr;

	//not sure if I can release the depth if I wanted?


	//create states
	D3D11_DEPTH_STENCIL_DESC t_DsDesc;

	// Depth test parameters
	t_DsDesc.DepthEnable = true;
	t_DsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	t_DsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	t_DsDesc.StencilEnable = true;
	t_DsDesc.StencilReadMask = 0xFF;
	t_DsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	t_DsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	t_DsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	t_DsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	t_DsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	t_DsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	t_DsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	t_DsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	t_DsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state

	hr = m_Device->CreateDepthStencilState(&t_DsDesc, &m_DepthStateOn);
	if (FAILED(hr))
		return hr;

	t_DsDesc.DepthEnable = false;
	t_DsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	hr = m_Device->CreateDepthStencilState(&t_DsDesc, &m_DepthStateOff);
	if (FAILED(hr))
		return hr;

	t_DsDesc.DepthEnable = true;
	t_DsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	t_DsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	hr = m_Device->CreateDepthStencilState(&t_DsDesc, &m_DepthStateNoWrite);
	if (FAILED(hr))
		return hr;

	t_DsDesc.DepthEnable = true;
	t_DsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	t_DsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	hr = m_Device->CreateDepthStencilState(&t_DsDesc, &m_LessEqualDepthState);


	m_DeviceContext->OMSetDepthStencilState(m_DepthStateOn, 0);

	return hr;
}

HRESULT Renderer::InitializeBlendAndStates()
{
	HRESULT hr = S_OK;

	D3D11_BLEND_DESC t_Blend_desc;
	t_Blend_desc.AlphaToCoverageEnable = false;
	t_Blend_desc.IndependentBlendEnable = false;


	t_Blend_desc.RenderTarget[0].BlendEnable = true;
	t_Blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	t_Blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	t_Blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	t_Blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	t_Blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	t_Blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	t_Blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


	hr = m_Device->CreateBlendState(&t_Blend_desc, &m_BlendStateOn);
	if (FAILED(hr))
		return hr;

	t_Blend_desc.RenderTarget[0].BlendEnable = false;
	hr = m_Device->CreateBlendState(&t_Blend_desc, &m_BlendStateOff);
	if (FAILED(hr))
		return hr;

	float t_BlendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_DeviceContext->OMSetBlendState(m_BlendStateOff, t_BlendFactors, 0xffffffff);

	return hr;
}

//not yet fixed
HRESULT Renderer::InitializeShaders() 
{
	HRESULT hr = S_OK;


	return hr;
}

//not yet fixed
HRESULT Renderer::InitializeConstantBuffers()
{
	HRESULT hr = S_OK;


	return hr;
}


HRESULT Renderer::InitializeGBuffers()
{
	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = *m_Width;
	desc.Height = *m_Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //changed from format DXGI_FORMAT_R16G16B16A16_UNORM
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;


	D3D11_SHADER_RESOURCE_VIEW_DESC t_SrvDesc;
	t_SrvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	t_SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	t_SrvDesc.Texture2D.MostDetailedMip = 0;
	t_SrvDesc.Texture2D.MipLevels = 1;


	for (int i = 0; i < 3; i++)
	{
		ID3D11Texture2D* t_Texture = 0;
		if (i == 2)
		{
			desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			t_SrvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		}

		hr = m_Device->CreateTexture2D(&desc, 0, &t_Texture);
		if (FAILED(hr))
			return hr;

		hr = m_Device->CreateShaderResourceView(t_Texture, &t_SrvDesc, &m_GbufferShaderResource[i]);
		if (FAILED(hr))
			return hr;

		hr = m_Device->CreateRenderTargetView(t_Texture, nullptr, &m_GbufferTargetViews[i]);
		if (FAILED(hr))
			return hr;


		t_Texture->Release();

	}


	return hr;
}

HRESULT Renderer::InitializeSamplerState()
{
	HRESULT hr = S_OK;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC; // D3D11_FILTER_ANISOTROPIC  D3D11_FILTER_MIN_MAG_MIP_LINEAR
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX; //D3D11_FLOAT32_MAX
	sampDesc.MaxAnisotropy = 16; //why not max it out when we can?
	hr = m_Device->CreateSamplerState(&sampDesc, &m_SamplerStateWrap);
	if (FAILED(hr))
		return hr;

	m_DeviceContext->VSSetSamplers(0, 1, &m_SamplerStateWrap);
	m_DeviceContext->HSSetSamplers(0, 1, &m_SamplerStateWrap);
	m_DeviceContext->DSSetSamplers(0, 1, &m_SamplerStateWrap);
	m_DeviceContext->GSSetSamplers(0, 1, &m_SamplerStateWrap);
	m_DeviceContext->PSSetSamplers(0, 1, &m_SamplerStateWrap);

	//for compute shader
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = m_Device->CreateSamplerState(&sampDesc, &m_SamplerStateLinearClamp);

	m_DeviceContext->CSSetSamplers(0, 1, &m_SamplerStateLinearClamp);


	return hr;
}

void Renderer::BeginRender()
{
	if (m_IsRendering)
	{
		MessageBox(nullptr, L"Rendering call Begin was called befor end was called.", L"ErrorMessage", MB_OK);
		return;
	}
	
	//clear the render target
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, Colors::Black);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	
	m_IsRendering = true;
}

void Renderer::RenderOpaque(RenderObjects* p_RenderObjects) //should be already sorted here on something,
{
	int t_NumOfObjects = p_RenderObjects->size();
	if (t_NumOfObjects == 0)
	{
		return;
	}

	//std::vector<ID3D11Buffer*> t_BuffersToDraw; //can be direct inputted into the IA stage
	std::vector<std::vector<Material*>> t_MaterialsPerBuffer; //is to be updated after each "draw"
	std::vector<XMFLOAT4X4> t_TranslationsPerMaterial; //should be able to be inputted aside with vertex buffer in the early AI stage

	ID3D11Buffer* t_VertexBuffer;
	Material* t_Material;
	std::vector<XMFLOAT4X4> t_Matrices;

	//ok so first we do it simple, only taking care of the vertex buffer with checking material as well, ok ? 
	{
		RenderObject t_RenderObject = p_RenderObjects->at(0);
		t_VertexBuffer = t_RenderObject.m_Mesh->GetVertexBuffer(t_RenderObject.BufferNum);
		t_Material = ((RenderComponent*)(t_RenderObject.m_Component))->GetMaterial(t_RenderObject.BufferNum); //woa... but yes
		TransformComponent* t_Transform = (TransformComponent*)(t_RenderObject.m_Component->GetEntity()->GetTransformComponent());
		t_Matrices.push_back(t_Transform->GetMatrix());
	}

	for (int i = 0; i < t_NumOfObjects; i++)
	{
		RenderObject t_RenderObject = p_RenderObjects->at(0);
		ID3D11Buffer* t_CheckVertexBuffer = t_RenderObject.m_Mesh->GetVertexBuffer(t_RenderObject.BufferNum);
		Material* t_CheckMaterial = ((RenderComponent*)(t_RenderObject.m_Component))->GetMaterial(t_RenderObject.BufferNum); //woa... but yes
		TransformComponent* t_Transform = (TransformComponent*)(t_RenderObject.m_Component->GetEntity()->GetTransformComponent());
		//can only have max 32 buffer in the IA stage, 

		if (t_VertexBuffer == t_CheckVertexBuffer && t_Material == t_CheckMaterial) //yey it's the same buffer.. what now? Check materialS?
		{
			t_Matrices.push_back(t_Transform->GetMatrix());
		}
		else
		{
			ID3D11Buffer* t_Buffer = {0};
			m_DeviceContext->UpdateSubresource(t_Buffer, 0, nullptr, &t_Matrices, 0, 0);

			//m_DeviceContext->IASetVertexBuffers(0, 2, , , ); //set both vertex and instance buffer
			//m_DeviceContext->IASetIndexBuffer();

			//m_DeviceContext->DrawIndexedInstanced();



			//reset the instanced buffer
			t_Matrices.clear();
			t_VertexBuffer = t_CheckVertexBuffer;
		}
	}
	

	//textures
	//vertexBuffers
	//materialBuffers?
	//matrixes
}

void Renderer::ComputeDeferred()
{

}

void Renderer::RenderTransparent(RenderObjects* p_RenderObjects)
{

}

void Renderer::EndRender()
{
	if (!m_IsRendering)
	{
		MessageBox(nullptr, L"Rendering call End was called befor begin was called.", L"ErrorMessage", MB_OK);
		return;
	}

	m_SwapChain->Present(0, 0);
	m_IsRendering = false;
}