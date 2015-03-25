#include "DirectXGraphicEngine.h"
#include "ShaderLoader.h"
#include "TextureLoaderDDS.h"

bool DirectXGraphicEngine::Initialize(HWND p_Handle, UINT p_Width, UINT p_Height)
{
	//convert here because we dont want windows outside engine if not windows :P
	m_Width = p_Width;
	m_Height = p_Height;

	HRESULT hr = S_OK;

	hr = InitializeDriverAndVersion(p_Handle);
	if (FAILED(hr))
		return false;

	hr = InitializeRenderTargetView();
	if (FAILED(hr))
		return false;

	hr = InitializeRasterizers();
	if (FAILED(hr))
		return false;

	InitializeViewport();

	hr = InitializeDeptpAndStates();
	if (FAILED(hr))
		return false;

	hr = InitializeBlendAndStates();
	if (FAILED(hr))
		return false;

	hr = InitializeSamplers();
	if (FAILED(hr))
		return false;

	
	hr = InitializeShaders();
	if (FAILED(hr))
		return false;

	hr = CreateErrorTexture();
	if (FAILED(hr))
		return false;

	/*
	hr = InitializeConstantBuffers();
	if (FAILED(hr))
		return false;

	hr = InitializeGBuffers();

	if (FAILED(hr))
		return false;
	
	*/

	return true;
}

//initialize directx D11.1 is newest we can use
HRESULT DirectXGraphicEngine::InitializeDriverAndVersion(HWND p_HandleWindow)
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//set types of drivers we allow
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	//set types of directx versions we support
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	//description of our backbuffer/swapchain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = m_Width;
	sd.BufferDesc.Height = m_Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS; //fixed for deferred rendering, set flag for input if want to put into a shader as well I guess
	sd.OutputWindow = p_HandleWindow;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//check what version computer supports, higher levels checked first
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

//create the rendertarget/unorderd from backbuffer
HRESULT DirectXGraphicEngine::InitializeRenderTargetView()
{
	HRESULT hr = S_OK;

	ID3D11Texture2D* t_BackBuffer = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&t_BackBuffer);
	if (FAILED(hr))
		return hr;

	hr = m_Device->CreateRenderTargetView(t_BackBuffer, nullptr, &m_RenderTargetView);
	if (FAILED(hr))
		return hr;

	hr = m_Device->CreateUnorderedAccessView(t_BackBuffer, nullptr, &m_UnorderedAccessView);
	if (FAILED(hr))
		return hr;

	t_BackBuffer->Release();


	return hr;
}

//creates the sceenviewport sized to the window
void DirectXGraphicEngine::InitializeViewport()
{
	D3D11_VIEWPORT vp;

	vp.Width = (FLOAT)m_Width;
	vp.Height = (FLOAT)m_Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_DeviceContext->RSSetViewports(1, &vp);
}

//creates normal,wireframe rasterizers
HRESULT DirectXGraphicEngine::InitializeRasterizers()
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

	hr = m_Device->CreateRasterizerState(&desc, &m_RasterizerNormal);
	if (FAILED(hr))
		return hr;

	desc.FillMode = D3D11_FILL_WIREFRAME;

	hr = m_Device->CreateRasterizerState(&desc, &m_RasterizerWireframe);
	if (FAILED(hr))
		return hr;
	

	m_DeviceContext->RSSetState(m_RasterizerNormal);

	return hr;
}

//creates depthbuffer and state for on/off
HRESULT DirectXGraphicEngine::InitializeDeptpAndStates()
{
	HRESULT hr = S_OK;

	// Create depth stencil texture of description
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = m_Width;
	descDepth.Height = m_Height;
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

	//create a view of the depthstencil texture we can use
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
	hr = m_Device->CreateDepthStencilState(&t_DsDesc, &m_DepthStencilStateOn);
	if (FAILED(hr))
		return hr;

	t_DsDesc.DepthEnable = false;
	t_DsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	hr = m_Device->CreateDepthStencilState(&t_DsDesc, &m_DepthStencilStateOff);
	if (FAILED(hr))
		return hr;

	//set normal state
	m_DeviceContext->OMSetDepthStencilState(m_DepthStencilStateOn, 0);

	return hr;
}

//creates blendstate for on/off
HRESULT DirectXGraphicEngine::InitializeBlendAndStates()
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

//creates all the default samplers used for shaders
HRESULT DirectXGraphicEngine::InitializeSamplers()
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
	hr = m_Device->CreateSamplerState(&sampDesc, &m_SamplerWrap);
	if (FAILED(hr))
		return hr;

	

	sampDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = m_Device->CreateSamplerState(&sampDesc, &m_SamplerClamp);
	if (FAILED(hr))
		return hr;

	//for compute shader
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS;

	sampDesc.BorderColor[0] = 1;
	sampDesc.BorderColor[1] = 1;
	sampDesc.BorderColor[2] = 1;
	sampDesc.BorderColor[3] = 1e5f;

	hr = m_Device->CreateSamplerState(&sampDesc, &m_SamplerBorder);

	sampDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = m_Device->CreateSamplerState(&sampDesc, &m_SamplerWrapRandom);

	//set sampelers for normal shading?
	m_DeviceContext->VSSetSamplers(0, 1, &m_SamplerWrap);
	m_DeviceContext->HSSetSamplers(0, 1, &m_SamplerWrap);
	m_DeviceContext->DSSetSamplers(0, 1, &m_SamplerWrap);
	m_DeviceContext->GSSetSamplers(0, 1, &m_SamplerWrap);
	m_DeviceContext->PSSetSamplers(0, 1, &m_SamplerWrap);

	//set samplers for compute shader shading
	m_DeviceContext->CSSetSamplers(2, 1, &m_SamplerBorder);
	m_DeviceContext->CSSetSamplers(1, 1, &m_SamplerWrapRandom);
	m_DeviceContext->CSSetSamplers(0, 1, &m_SamplerClamp);


	return hr;
}

//not fully yet fixed
HRESULT DirectXGraphicEngine::InitializeShaders()
{
	HRESULT hr = S_OK;

	ShaderLoader t_ShaderLoader = ShaderLoader();

	////DEFERRED RENDERING OPAQUE
	{
		ID3D11VertexShader* t_VertexShader;
		ID3D11InputLayout* t_InputLayout;

		D3D11_INPUT_ELEMENT_DESC t_Layout[] =
		{
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "WORLDMATRIX",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX",	1, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX",	2, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{ "WORLDMATRIX",	3, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },

		};
		UINT t_NumElements = ARRAYSIZE(t_Layout);

		hr = t_ShaderLoader.CreateVertexShaderWithInputLayout(L"Shaders/OpaqueVS.hlsl", "VS", "vs_5_0", m_Device, &t_VertexShader, t_Layout, t_NumElements, &t_InputLayout);
		if (FAILED(hr))
			return hr;

		

		ID3D11PixelShader* t_PixelShader;
		hr = t_ShaderLoader.CreatePixelShader(L"Shaders/OpaquePS.hlsl", "PS", "ps_5_0", m_Device, &t_PixelShader);
		if (FAILED(hr))
			return hr;

		m_OpaqueShaders = new ShaderProgram();
		m_OpaqueShaders->VertexShader = t_VertexShader;
		m_OpaqueShaders->InputLayout = t_InputLayout;
		m_OpaqueShaders->PixelShader = t_PixelShader;
	}

	////DEFERRED COMPUTE SHADER
	{
		m_DeferredComputeShader = new ShaderProgram();

		ID3D11ComputeShader* t_ComputeShader;
		hr = t_ShaderLoader.CreateComputeShader(L"DeferredCS.hlsl", "CS", "cs_5_0", m_Device, &t_ComputeShader);
		if (FAILED(hr))
			return hr;

		m_DeferredComputeShader->ComputeShader = t_ComputeShader;
	}

	return hr;
}

//not yet fixed
HRESULT DirectXGraphicEngine::InitializeConstantBuffers()
{
	HRESULT hr = S_OK;

	////Instance buffer
	{
		D3D11_BUFFER_DESC t_ibd;
		t_ibd.Usage = D3D11_USAGE_DYNAMIC; // D3D11_USAGE_DEFAULT  D3D11_USAGE_DYNAMIC
		t_ibd.ByteWidth = sizeof(XMMATRIX)* m_MaxNumOfInstances;
		t_ibd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		t_ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //D3D11_CPU_ACCESS_WRITE
		t_ibd.MiscFlags = 0;
		t_ibd.StructureByteStride = 0;

		hr = m_Device->CreateBuffer(&t_ibd, 0, &m_InstanceBuffer);
		if (FAILED(hr))
			return hr;
	}

	//Shader Constant buffers
	{
		D3D11_BUFFER_DESC t_BufferDesc;
		t_BufferDesc.MiscFlags = 0;
		t_BufferDesc.StructureByteStride = 0;
		t_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		t_BufferDesc.ByteWidth = sizeof(DeferredComputeCBuffer);
		t_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		t_BufferDesc.CPUAccessFlags = 0;

		hr = m_Device->CreateBuffer(&t_BufferDesc, 0, &m_DeferredComputeCBuffer);
		if (FAILED(hr))
			return hr;


		t_BufferDesc.ByteWidth = sizeof(PerFrameCBuffer);
		t_BufferDesc.CPUAccessFlags = 0;

		hr = m_Device->CreateBuffer(&t_BufferDesc, 0, &m_PerFrameCBuffer);
		if (FAILED(hr))
			return hr;
		
	}


	//set buffers to different shaderstages
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_PerFrameCBuffer);
	m_DeviceContext->CSSetConstantBuffers(0, 1, &m_PerFrameCBuffer);
	m_DeviceContext->CSSetConstantBuffers(1, 1, &m_DeferredComputeCBuffer);
	return hr;
}

//not yet fixed
HRESULT DirectXGraphicEngine::InitializeGBuffers()
{
	HRESULT hr = S_OK;

	//description for GBuffers
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = m_Width;
	desc.Height = m_Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //changed from format DXGI_FORMAT_R16G16B16A16_UNORM
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; //both read and output
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;


	D3D11_SHADER_RESOURCE_VIEW_DESC t_SrvDesc;
	t_SrvDesc.Format = desc.Format;
	t_SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	t_SrvDesc.Texture2D.MostDetailedMip = 0;
	t_SrvDesc.Texture2D.MipLevels = 1;

	//create the 3 gbuffers first is Norml/depth, second is Diffuse+spec, 3d isn't set but was used for glow
	for (int i = 0; i < 3; i++)
	{
		//the last changes to be 
		if (i == 2)
		{
			desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			t_SrvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		}

		ID3D11Texture2D* t_Texture = 0;
		hr = m_Device->CreateTexture2D(&desc, 0, &t_Texture);
		if (FAILED(hr))
			return hr;

		hr = m_Device->CreateShaderResourceView(t_Texture, &t_SrvDesc, &m_GBufferSRV[i]);
		if (FAILED(hr))
			return hr;

		hr = m_Device->CreateRenderTargetView(t_Texture, nullptr, &m_GBufferRTV[i]);
		if (FAILED(hr))
			return hr;


		t_Texture->Release();

	}



	return hr;
}


bool DirectXGraphicEngine::LoadPresetFromFile()
{
	return true;
}

HRESULT DirectXGraphicEngine::CreateErrorTexture()
{
	HRESULT hr = S_OK;

	ID3D11ShaderResourceView* t_NewResourceView;
	
	std::string t_Name = "ERROR_TEXTURE.dds";
	std::string t_FilePath = "Textures/" + t_Name;
	std::wstring t_LoadTextString = std::wstring(t_FilePath.begin(), t_FilePath.end());

	hr = CreateDDSTextureFromFile(m_Device, t_LoadTextString.c_str(), nullptr, &t_NewResourceView);
	if (SUCCEEDED(hr))
	{
		std::hash<ID3D11ShaderResourceView*> t_Hasher;
		UINT t_Value = t_Hasher(t_NewResourceView);

		m_TextureMap[t_NewResourceView] = t_Value;
		m_TextureIDMap[t_Name] = t_Value;
		m_ErrorTextureID = t_Value;
	}

	return hr;
}