#include "Renderer.h"
#include <DirectXColors.h>
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "ShaderLoader.h"
#include "DDSTextureLoader.h"

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
	m_AmountOfPointLights = 0;
	m_DeferredShaderProgram = new ShaderProgram();
	m_ShadowMapShaderProgram = new ShaderProgram();
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

	//InitializeViewports();

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

	//test stuff
	
	m_PointLights[m_AmountOfPointLights] = PointLight(XMFLOAT3(1,6,-19), 30, XMFLOAT3(1,1,1));
	m_AmountOfPointLights++;
	m_PointLights[m_AmountOfPointLights] = PointLight(XMFLOAT3(4, 6, -13), 30, XMFLOAT3(1, 0, 0));

	m_DeviceContext->UpdateSubresource(m_PointLightsBuffer, 0, nullptr, &m_PointLights[0], 0, 0);

	PerComputeBuffer t_PerCompute;
	t_PerCompute.AmbientLight = XMFLOAT4(0.1f,0.1f,0.1f,0);
	t_PerCompute.CamNearFar = XMFLOAT2(0.5f, 10000.0f);
	t_PerCompute.ColorOverlay = XMFLOAT4(0.0f, 0, 0, 0);
	t_PerCompute.ScreenDimensions = XMFLOAT2(1920, 1080);

	m_DeviceContext->UpdateSubresource(m_PerComputeBuffer, 0, nullptr, &t_PerCompute, 0, 0);

	m_ShadowMap = new ShadowMap(m_Device, 2048, 2048);
	CameraStruct t_Cam;
	t_Cam.Position = XMFLOAT3(1, 0, 0);
	
	XMVECTOR t_Eye = XMLoadFloat3(&XMFLOAT3(0, 10, -15));
	XMVECTOR t_At = XMLoadFloat3(&XMFLOAT3(0, 0, 0));
	XMVECTOR t_Up = XMLoadFloat3(&XMFLOAT3(0, 1, 0));
	XMStoreFloat4x4(&t_Cam.Proj, XMMatrixOrthographicLH(2048, 2048, 0, 10000.0f));
	XMStoreFloat4x4(&t_Cam.View, XMMatrixLookAtLH(t_Eye, t_At, t_Up));

	m_ShadowMapMatrices.push_back(t_Cam);

	return true;
}

void Renderer::CreateBuffer(D3D11_BUFFER_DESC* p_Desc, D3D11_SUBRESOURCE_DATA* p_Data, ID3D11Buffer** o_Buffer)
{
	HRESULT hr = m_Device->CreateBuffer(p_Desc, p_Data, o_Buffer);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Buffer could not be created", L"Error", MB_ICONERROR | MB_OK);
	}
}

bool Renderer::CreateTexture(const wchar_t * p_FileName, ID3D11ShaderResourceView** t_NewSRV)
{
	HRESULT hr = S_OK;
	
	hr = CreateDDSTextureFromFile(m_Device, p_FileName, nullptr, t_NewSRV);

	if (FAILED(hr))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Renderer::SetViewports(std::vector<D3D11_VIEWPORT> p_Viewports)
{
	m_Viewports = p_Viewports;
}

void Renderer::SetCameras(std::vector<Renderer::CameraStruct> p_Cameras)
{
	m_Cameras = p_Cameras;
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

//void Renderer::InitializeViewports()
//{
//	D3D11_VIEWPORT vp;
//
//	vp.Width = (FLOAT)*m_Width;
//	vp.Height = (FLOAT)*m_Height;
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	vp.TopLeftX = 0;
//	vp.TopLeftY = 0;
//
//	m_DeviceContext->RSSetViewports(1, &vp);
//}

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
	//m_DeviceContext->OMSetBlendState(m_BlendStateOff, t_BlendFactors, 0xffffffff);

	return hr;
}

//not yet fixed
HRESULT Renderer::InitializeShaders() 
{
	HRESULT hr = S_OK;

	ShaderLoader t_ShaderLoader = ShaderLoader();
	////DEFERRED RENDERING
	{
		ID3D11VertexShader* t_VertexShader;
		ID3D11InputLayout* t_InputLayout;

		D3D11_INPUT_ELEMENT_DESC t_Layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "WORLDMATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },

		};
		UINT t_NumElements = ARRAYSIZE(t_Layout);

		hr = t_ShaderLoader.CreateVertexShaderWithInputLayout(L"DeferredVS.hlsl", "VS", "vs_5_0", m_Device, &t_VertexShader, t_Layout, t_NumElements, &t_InputLayout);
		if (FAILED(hr))
			return hr;

		m_DeferredShaderProgram->VertexShader = t_VertexShader;
		m_DeferredShaderProgram->InputLayout = t_InputLayout;
	}

	{
		ID3D11PixelShader* t_PixelShader;
		hr = t_ShaderLoader.CreatePixelShader(L"DeferredPS.hlsl", "PS", "ps_5_0", m_Device, &t_PixelShader);
		if (FAILED(hr))
			return hr;
		m_DeferredShaderProgram->PixelShader = t_PixelShader;
	}

	{
		hr = t_ShaderLoader.CreateComputeShader(L"DeferredCS.hlsl", "CS", "cs_5_0", m_Device, &m_DeferredCS);
		if (FAILED(hr))
			return hr;
	}

	////SHADOW MAPS
	{
		ID3D11VertexShader* t_VertexShader;
		ID3D11InputLayout* t_InputLayout;

		D3D11_INPUT_ELEMENT_DESC t_Layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "WORLDMATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },

		};
		UINT t_NumElements = ARRAYSIZE(t_Layout);

		hr = t_ShaderLoader.CreateVertexShaderWithInputLayout(L"ShadowMapVS.hlsl", "VS", "vs_5_0", m_Device, &t_VertexShader, t_Layout, t_NumElements, &t_InputLayout);
		if (FAILED(hr))
			return hr;

		m_ShadowMapShaderProgram->VertexShader = t_VertexShader;
		m_ShadowMapShaderProgram->InputLayout = t_InputLayout;
	}

	{
		ID3D11PixelShader* t_PixelShader;
		hr = t_ShaderLoader.CreatePixelShader(L"ShadowMapPS.hlsl", "PS", "ps_5_0", m_Device, &t_PixelShader);
		if (FAILED(hr))
			return hr;
		m_ShadowMapShaderProgram->PixelShader = t_PixelShader;
	}

	return hr;
}

//not yet fixed
HRESULT Renderer::InitializeConstantBuffers()
{
	HRESULT hr = S_OK;
	{
		D3D11_BUFFER_DESC t_ibd;
		t_ibd.Usage = D3D11_USAGE_DYNAMIC; // D3D11_USAGE_DEFAULT  D3D11_USAGE_DYNAMIC
		t_ibd.ByteWidth = sizeof(XMMATRIX)* MAX_INSTANCEBUFFER_SIZE;
		t_ibd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		t_ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //D3D11_CPU_ACCESS_WRITE
		t_ibd.MiscFlags = 0;
		t_ibd.StructureByteStride = 0;

		hr = m_Device->CreateBuffer(&t_ibd, 0, &m_InstanceBuffer);
		if (FAILED(hr))
			return hr;


		t_ibd.Usage = D3D11_USAGE_DEFAULT;
		t_ibd.ByteWidth = sizeof(PerFrameTestBuffer);
		t_ibd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		t_ibd.CPUAccessFlags = 0;

		hr = m_Device->CreateBuffer(&t_ibd, 0, &m_TestPerFrameBuffer);
		if (FAILED(hr))
			return hr;

		m_DeviceContext->VSSetConstantBuffers(0, 1, &m_TestPerFrameBuffer);
		m_DeviceContext->CSSetConstantBuffers(0, 1, &m_TestPerFrameBuffer);
	}
	{
		D3D11_BUFFER_DESC t_BufferDesc;
		t_BufferDesc.MiscFlags = 0;
		t_BufferDesc.StructureByteStride = 0;
		t_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		t_BufferDesc.ByteWidth = sizeof(PerComputeBuffer);
		t_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		t_BufferDesc.CPUAccessFlags = 0;

		hr = m_Device->CreateBuffer(&t_BufferDesc, 0, &m_PerComputeBuffer);
		if (FAILED(hr))
			return hr;

		m_DeviceContext->CSSetConstantBuffers(1, 1, &m_PerComputeBuffer);
	}

	{
		D3D11_BUFFER_DESC t_BufferDesc;
		ZeroMemory(&t_BufferDesc, sizeof(t_BufferDesc));
		t_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		t_BufferDesc.CPUAccessFlags = 0;

		m_PointLights.resize(MAX_NUM_OF_LIGHTS);
		/*bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.Usage = D3D11_USAGE_DYNAMIC;*/
		t_BufferDesc.ByteWidth = sizeof(PointLight)*MAX_NUM_OF_LIGHTS;
		t_BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		t_BufferDesc.StructureByteStride = sizeof(PointLight);
		t_BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		D3D11_SUBRESOURCE_DATA t_InitData;
		t_InitData.pSysMem = &m_PointLights[0];

		hr = m_Device->CreateBuffer(&t_BufferDesc, &t_InitData, &m_PointLightsBuffer);
		if (FAILED(hr))
			return hr;

		D3D11_SHADER_RESOURCE_VIEW_DESC t_SrvDesc;
		t_SrvDesc.Format = DXGI_FORMAT_UNKNOWN;
		t_SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
		t_SrvDesc.BufferEx.FirstElement = 0;
		t_SrvDesc.BufferEx.Flags = 0;
		t_SrvDesc.BufferEx.NumElements = MAX_NUM_OF_LIGHTS;

		hr = m_Device->CreateShaderResourceView(m_PointLightsBuffer, &t_SrvDesc, &m_PointLightsBufferSRV);
	}
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

void Renderer::SetShaders(ShaderProgram* p_Program) //test
{
	if (p_Program->ComputeShader != nullptr)
	{
		m_DeviceContext->CSSetShader(p_Program->ComputeShader,nullptr,0);
		return;
	}
	if (p_Program->InputLayout != nullptr)
	{
		m_DeviceContext->IASetInputLayout(p_Program->InputLayout);
	}
	if (p_Program->VertexShader != nullptr)
	{
		m_DeviceContext->VSSetShader(p_Program->VertexShader, nullptr, 0);
	}
	if (p_Program->GeometryShader != nullptr)
	{
		m_DeviceContext->GSSetShader(p_Program->GeometryShader, nullptr, 0);
	}
	if (p_Program->HullShader != nullptr)
	{
		m_DeviceContext->HSSetShader(p_Program->HullShader, nullptr, 0);
	}
	if (p_Program->DomainShader != nullptr)
	{
		m_DeviceContext->DSSetShader(p_Program->DomainShader, nullptr, 0);
	}
	if (p_Program->PixelShader != nullptr)
	{
		m_DeviceContext->PSSetShader(p_Program->PixelShader, nullptr, 0);
	}
}

void Renderer::SetTextures(RenderObject* p_Object)
{
	RenderComponent* t_Comp = (RenderComponent*)p_Object->m_Component;
	Material* t_Mat = t_Comp->GetMaterial(p_Object->BufferNum);

	
	std::map<std::string, Texture*>* m_Textures = t_Mat->GetTextures();
	if (m_Textures->size() >= 2)
	{
		std::map<std::string, Texture*>::iterator t_It;

		t_It = m_Textures->find("DIFFUSE");
		if (t_It != m_Textures->end())
		{
			ID3D11ShaderResourceView* t_Resource = t_It->second->GetTextureView();
			m_DeviceContext->PSSetShaderResources(0, 1, &t_Resource);
		}

		t_It = m_Textures->find("NORMAL");
		if (t_It != m_Textures->end())
		{
			ID3D11ShaderResourceView* t_Resource = t_It->second->GetTextureView();
			m_DeviceContext->PSSetShaderResources(1, 1, &t_Resource);
		}
	}
	else
	{
		MessageBox(nullptr, L"Well.. SetTexture function failed not enought textures...", L"ErrorMessage", MB_OK);
	}
}

void Renderer::SetPerFrameBuffers(std::vector<CameraStruct>* p_Cameras)
{
	//set cameras
	if (p_Cameras->size() != 0)
	{
		int t_NumOfCameras = p_Cameras->size();
		PerFrameTestBuffer t_PerFrameBuffer;

		t_PerFrameBuffer.Proj = XMMatrixTranspose(XMLoadFloat4x4(&p_Cameras->at(0).Proj));
		t_PerFrameBuffer.View = XMMatrixTranspose(XMLoadFloat4x4(&p_Cameras->at(0).View));
		XMFLOAT3 t_Pos = p_Cameras->at(0).Position;
		t_PerFrameBuffer.EyePosition = XMFLOAT4(t_Pos.x, t_Pos.y, t_Pos.z, 0);
		//t_PerFrameBuffer.ViewProj = XMMatrixTranspose( XMLoadFloat4x4(&m_Cameras[0].ViewProj));

		m_DeviceContext->UpdateSubresource(m_TestPerFrameBuffer, 0, nullptr, &t_PerFrameBuffer, 0, 0); //be aware of change
	}
	else
	{
		CameraStruct t_Temp;
		XMFLOAT4X4 t_Mat;
		XMStoreFloat4x4(&t_Mat, XMMatrixIdentity());
		t_Temp.Proj = t_Mat;
		t_Temp.View = t_Mat;
		//t_Temp.ViewProj = t_Mat;
		m_DeviceContext->UpdateSubresource(m_TestPerFrameBuffer, 0, nullptr, &t_Temp, 0, 0);
	}
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

	for (int i = 0; i < 3; i++)
	{
		m_DeviceContext->ClearRenderTargetView(m_GbufferTargetViews[i], Colors::Black);
	}

	SetPerFrameBuffers(&m_Cameras);
	
	m_IsRendering = true;
}

void Renderer::RenderOpaque(RenderObjects* p_RenderObjects) //should be already sorted here on something,
{
	m_DeviceContext->RSSetViewports(m_Viewports.size(), &m_Viewports[0]);

	SetShaders(m_DeferredShaderProgram);
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_DeviceContext->OMSetRenderTargets(3, m_GbufferTargetViews, m_DepthStencilView);

	int t_NumOfObjects = p_RenderObjects->size();
	if (t_NumOfObjects == 0)
	{
		return;
	}

	//std::vector<ID3D11Buffer*> t_BuffersToDraw; //can be direct inputted into the IA stage
	std::vector<std::vector<Material*>> t_MaterialsPerBuffer; //is to be updated after each "draw"
	std::vector<XMFLOAT4X4> t_TranslationsPerMaterial; //should be able to be inputted aside with vertex buffer in the early AI stage

	ID3D11Buffer* t_VertexBuffer;
	ID3D11Buffer* t_IndexBuffer;
	Material* t_Material;
	std::vector<XMMATRIX> t_Matrices;


	UINT strides[2] = { sizeof(Mesh::MeshVertex), sizeof(XMMATRIX) };
	UINT offsets[2] = { 0 , 0};
	UINT indexOffset = 0;
	int t_VertexBuffSize = 0;
	int t_NumOfInstances = 0;
	RenderObject* t_RenderObject;
	//ok so first we do it simple, only taking care of the vertex buffer with checking material as well, ok ? 
	{
		t_RenderObject = p_RenderObjects->at(0);
		RenderComponent* t_RenderComponent = ((RenderComponent*)(t_RenderObject->m_Component));

		t_VertexBuffer = t_RenderComponent->GetMesh()->GetVertexBuffer(t_RenderObject->BufferNum);
		t_IndexBuffer = t_RenderComponent->GetMesh()->GetIndexBuffer(t_RenderObject->BufferNum);
		t_VertexBuffSize = t_RenderComponent->GetMesh()->GetNumOfIndecies(t_RenderObject->BufferNum);

		t_Material = t_RenderComponent->GetMaterial(t_RenderObject->BufferNum); //woa... but yes
		TransformComponent* t_Transform = (TransformComponent*)(t_RenderObject->m_Component->GetEntity()->GetTransformComponent());
		t_Matrices.push_back(XMMatrixTranspose( XMLoadFloat4x4( &t_Transform->GetMatrix() )));
		t_NumOfInstances++;
	}
 	for (int i = 1; i < t_NumOfObjects; i++)
 	{
 		t_RenderObject = p_RenderObjects->at(i);
 		RenderComponent* t_RenderComponent = ((RenderComponent*)(t_RenderObject->m_Component));
 
 		ID3D11Buffer* t_CheckVertexBuffer = t_RenderComponent->GetMesh()->GetVertexBuffer(t_RenderObject->BufferNum);
 		Material* t_CheckMaterial = t_RenderComponent->GetMaterial(t_RenderObject->BufferNum); //woa... but yes
 
 		TransformComponent* t_Transform = (TransformComponent*)(t_RenderObject->m_Component->GetEntity()->GetTransformComponent());
 		//can only have max 32 buffer in the IA stage, 
 
 		if (t_VertexBuffer == t_CheckVertexBuffer && t_Material == t_CheckMaterial) //yey it's the same buffer.. what now?
 		{
 			t_Matrices.push_back(XMMatrixTranspose( XMLoadFloat4x4(&t_Transform->GetMatrix())));
 			t_NumOfInstances++;
 		}
 		else
 		{
 			//m_DeviceContext->UpdateSubresource(m_InstanceBuffer, 0, nullptr, &t_Matrices[0], 0, 0);
 
 			//update the instance buffer
 			D3D11_MAPPED_SUBRESOURCE t_MappedData;
 			HRESULT hr = m_DeviceContext->Map(m_InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MappedData);
 			XMMATRIX* dataView = reinterpret_cast<XMMATRIX*>(t_MappedData.pData);
 
 			int t_NumOfMatrices = t_Matrices.size();
 			for (int i = 0; i < t_NumOfMatrices; i++)
 			{
 				dataView[i] = t_Matrices[i];
 			}
 			
 			m_DeviceContext->Unmap(m_InstanceBuffer, 0);
 
 			ID3D11Buffer* t_InBuffers[2] = { t_VertexBuffer, m_InstanceBuffer };
 			

			SetTextures(t_RenderObject);

 			m_DeviceContext->IASetVertexBuffers(0, 2, t_InBuffers, strides, offsets); //set both vertex and instance buffer
 			m_DeviceContext->IASetIndexBuffer(t_IndexBuffer, DXGI_FORMAT_R32_UINT, indexOffset);
 			//m_DeviceContext->IASetIndexBuffer();
 
 			m_DeviceContext->DrawIndexedInstanced( t_VertexBuffSize, t_NumOfInstances,0,0,0);
 
 			//m_DeviceContext->DrawInstanced(t_VertexBuffSize, t_NumOfInstances, 0, 0);
 
 			//reset the instanced buffer
 			RenderComponent* t_RenderComponent = ((RenderComponent*)(t_RenderObject->m_Component));
 			t_Matrices.clear();
 			t_Matrices.push_back(XMMatrixTranspose( XMLoadFloat4x4( &t_Transform->GetMatrix())) );
 			t_VertexBuffer = t_CheckVertexBuffer;
 			t_IndexBuffer = t_RenderComponent->GetMesh()->GetIndexBuffer(t_RenderObject->BufferNum);
 			t_VertexBuffSize = t_RenderComponent->GetMesh()->GetNumOfIndecies(t_RenderObject->BufferNum);
 			t_NumOfInstances = 1;
 		}
 	}
	{
		//last one fix?
		D3D11_MAPPED_SUBRESOURCE t_MappedData;
		HRESULT hr = m_DeviceContext->Map(m_InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MappedData);
		XMMATRIX* dataView = reinterpret_cast<XMMATRIX*>(t_MappedData.pData);

		int t_NumOfMatrices = t_Matrices.size();
		for (int i = 0; i < t_NumOfMatrices; i++)
		{
			dataView[i] = t_Matrices[i];
		}

		m_DeviceContext->Unmap(m_InstanceBuffer, 0);

		SetTextures(t_RenderObject);
		ID3D11Buffer* t_InBuffers[2] = { t_VertexBuffer, m_InstanceBuffer };
		m_DeviceContext->IASetVertexBuffers(0, 2, t_InBuffers, strides, offsets);
		m_DeviceContext->IASetIndexBuffer(t_IndexBuffer, DXGI_FORMAT_R32_UINT, indexOffset);


		m_DeviceContext->DrawIndexedInstanced(t_VertexBuffSize, t_NumOfInstances, 0, 0, 0);
	}

	ID3D11RenderTargetView* t_Deleters[3] = { 0, 0, 0 };
	m_DeviceContext->OMSetRenderTargets(3, t_Deleters, m_DepthStencilView);
}

void Renderer::RenderShadowmaps(RenderObjects* p_RenderObjects)
{
	SetShaders(m_ShadowMapShaderProgram);

	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_ShadowMap->PrepareDraw(m_DeviceContext);

	int t_NumOfObjects = p_RenderObjects->size();
	if (t_NumOfObjects == 0)
	{
		return;
	}


	std::vector<std::vector<Material*>> t_MaterialsPerBuffer; //is to be updated after each "draw"
	std::vector<XMFLOAT4X4> t_TranslationsPerMaterial; //should be able to be inputted aside with vertex buffer in the early AI stage

	ID3D11Buffer* t_VertexBuffer;
	ID3D11Buffer* t_IndexBuffer;
	Material* t_Material;
	std::vector<XMMATRIX> t_Matrices;


	UINT strides[2] = { sizeof(Mesh::MeshVertex), sizeof(XMMATRIX) };
	UINT offsets[2] = { 0, 0 };
	UINT indexOffset = 0;
	int t_VertexBuffSize = 0;
	int t_NumOfInstances = 0;
	RenderObject* t_RenderObject;
	//ok so first we do it simple, only taking care of the vertex buffer with checking material as well, ok ? 
	{
		t_RenderObject = p_RenderObjects->at(0);
		RenderComponent* t_RenderComponent = ((RenderComponent*)(t_RenderObject->m_Component));

		t_VertexBuffer = t_RenderComponent->GetMesh()->GetVertexBuffer(t_RenderObject->BufferNum);
		t_IndexBuffer = t_RenderComponent->GetMesh()->GetIndexBuffer(t_RenderObject->BufferNum);
		t_VertexBuffSize = t_RenderComponent->GetMesh()->GetNumOfIndecies(t_RenderObject->BufferNum);

		t_Material = t_RenderComponent->GetMaterial(t_RenderObject->BufferNum); //woa... but yes
		TransformComponent* t_Transform = (TransformComponent*)(t_RenderObject->m_Component->GetEntity()->GetTransformComponent());
		t_Matrices.push_back(XMMatrixTranspose(XMLoadFloat4x4(&t_Transform->GetMatrix())));
		t_NumOfInstances++;
	}
	for (int i = 1; i < t_NumOfObjects; i++)
	{
		t_RenderObject = p_RenderObjects->at(i);
		RenderComponent* t_RenderComponent = ((RenderComponent*)(t_RenderObject->m_Component));

		ID3D11Buffer* t_CheckVertexBuffer = t_RenderComponent->GetMesh()->GetVertexBuffer(t_RenderObject->BufferNum);
		Material* t_CheckMaterial = t_RenderComponent->GetMaterial(t_RenderObject->BufferNum); //woa... but yes

		TransformComponent* t_Transform = (TransformComponent*)(t_RenderObject->m_Component->GetEntity()->GetTransformComponent());
		//can only have max 32 buffer in the IA stage, 

		if (t_VertexBuffer == t_CheckVertexBuffer && t_Material == t_CheckMaterial) //yey it's the same buffer.. what now?
		{
			t_Matrices.push_back(XMMatrixTranspose(XMLoadFloat4x4(&t_Transform->GetMatrix())));
			t_NumOfInstances++;
		}
		else
		{
			//m_DeviceContext->UpdateSubresource(m_InstanceBuffer, 0, nullptr, &t_Matrices[0], 0, 0);

			//update the instance buffer
			D3D11_MAPPED_SUBRESOURCE t_MappedData;
			HRESULT hr = m_DeviceContext->Map(m_InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MappedData);
			XMMATRIX* dataView = reinterpret_cast<XMMATRIX*>(t_MappedData.pData);

			int t_NumOfMatrices = t_Matrices.size();
			for (int i = 0; i < t_NumOfMatrices; i++)
			{
				dataView[i] = t_Matrices[i];
			}

			m_DeviceContext->Unmap(m_InstanceBuffer, 0);

			ID3D11Buffer* t_InBuffers[2] = { t_VertexBuffer, m_InstanceBuffer };

			m_DeviceContext->IASetVertexBuffers(0, 2, t_InBuffers, strides, offsets); //set both vertex and instance buffer
			m_DeviceContext->IASetIndexBuffer(t_IndexBuffer, DXGI_FORMAT_R32_UINT, indexOffset);
			//m_DeviceContext->IASetIndexBuffer();

			m_DeviceContext->DrawIndexedInstanced(t_VertexBuffSize, t_NumOfInstances, 0, 0, 0);

			//m_DeviceContext->DrawInstanced(t_VertexBuffSize, t_NumOfInstances, 0, 0);

			//reset the instanced buffer
			RenderComponent* t_RenderComponent = ((RenderComponent*)(t_RenderObject->m_Component));
			t_Matrices.clear();
			t_Matrices.push_back(XMMatrixTranspose(XMLoadFloat4x4(&t_Transform->GetMatrix())));
			t_VertexBuffer = t_CheckVertexBuffer;
			t_IndexBuffer = t_RenderComponent->GetMesh()->GetIndexBuffer(t_RenderObject->BufferNum);
			t_VertexBuffSize = t_RenderComponent->GetMesh()->GetNumOfIndecies(t_RenderObject->BufferNum);
			t_NumOfInstances = 1;
		}
	}
	{
		//last one fix?
		D3D11_MAPPED_SUBRESOURCE t_MappedData;
		HRESULT hr = m_DeviceContext->Map(m_InstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &t_MappedData);
		XMMATRIX* dataView = reinterpret_cast<XMMATRIX*>(t_MappedData.pData);

		int t_NumOfMatrices = t_Matrices.size();
		for (int i = 0; i < t_NumOfMatrices; i++)
		{
			dataView[i] = t_Matrices[i];
		}

		m_DeviceContext->Unmap(m_InstanceBuffer, 0);


		ID3D11Buffer* t_InBuffers[2] = { t_VertexBuffer, m_InstanceBuffer };
		m_DeviceContext->IASetVertexBuffers(0, 2, t_InBuffers, strides, offsets);
		m_DeviceContext->IASetIndexBuffer(t_IndexBuffer, DXGI_FORMAT_R32_UINT, indexOffset);

		m_DeviceContext->DrawIndexedInstanced(t_VertexBuffSize, t_NumOfInstances, 0, 0, 0);
	}

	ID3D11RenderTargetView* t_NullView = { 0 };
	m_DeviceContext->OMSetRenderTargets(1, &t_NullView, m_DepthStencilView);
}

void Renderer::ComputeDeferred()
{
	SetPerFrameBuffers(&m_Cameras);
	
	m_DeviceContext->CSSetShader(m_DeferredCS, nullptr, 0);


	m_DeviceContext->CSSetUnorderedAccessViews(0, 1, &m_BackBufferUAV, nullptr);
	m_DeviceContext->CSSetShaderResources(1, 3, m_GbufferShaderResource);
	m_DeviceContext->CSSetShaderResources(4, 1, &m_PointLightsBufferSRV);

	UINT x = ceil(*m_Width / (FLOAT)THREAD_BLOCK_DIMENSIONS);
	UINT y = ceil(*m_Height / (FLOAT)THREAD_BLOCK_DIMENSIONS);

	m_DeviceContext->Dispatch(x, y, 1);

	ID3D11ShaderResourceView* t_TempDelete1[3] = { 0, 0, 0 };
	m_DeviceContext->CSSetShaderResources(1, 3, t_TempDelete1);

	ID3D11UnorderedAccessView* t_TempDelete2 = { 0 };
	m_DeviceContext->CSSetUnorderedAccessViews(0, 1, &t_TempDelete2, nullptr);
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

	m_SwapChain->Present(1, 0);
	m_IsRendering = false;
}