#include "TextureResourceLoadSave.h"
#include "Renderer.h"

Resource* TextureResourceLoadSave::Load(std::string p_FileName)
{
	Renderer* m_Renderer = m_Renderer->GetInstance();
	ID3D11ShaderResourceView* t_NewSRV;
	std::wstring t_LoadTextString = std::wstring(p_FileName.begin(), p_FileName.end());

	bool t_Success = m_Renderer->CreateTexture(t_LoadTextString.c_str(), &t_NewSRV);

	if (!t_Success)
	{
		std::wstring t_Message = L"Couldn't load Texture " + t_LoadTextString;
		MessageBox(nullptr,  t_Message.c_str() , L"ErrorMessage", MB_OK);
		return nullptr;
	}
	else
	{
		Texture* t_NewTexture = new Texture();
		t_NewTexture->SetTextureView(t_NewSRV);
	}
}

void TextureResourceLoadSave::Save(Resource* p_File)
{
	std::string p_FileName = p_File->GetName();
	std::wstring t_LoadTextString = std::wstring(p_FileName.begin(), p_FileName.end());
	std::wstring t_Message = L"Can't save textures, regarding " + t_LoadTextString;
	MessageBox(nullptr, t_Message.c_str(), L"ErrorMessage", MB_OK);
}

const char* TextureResourceLoadSave::GetExtension()
{
	return ".dds";
}
