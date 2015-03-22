#include "TextureResourceLoadSave.h"
#include "Renderer.h"
#include "Logger.h"

Resource* TextureResourceLoadSave::Load(std::string p_FileName)
{
	Renderer* m_Renderer = m_Renderer->GetInstance();
	ID3D11ShaderResourceView* t_NewSRV;
	std::string t_FilePath = "Graphics/Textures/" + p_FileName;
	
	std::wstring t_LoadTextString = std::wstring(t_FilePath.begin(), t_FilePath.end());

	bool t_Success = m_Renderer->CreateTexture(t_LoadTextString.c_str(), &t_NewSRV);

	if (!t_Success)
	{
		std::string t_Message = "Couldn't load Texture " + t_FilePath;
		//MessageBox(nullptr,  t_Message.c_str() , L"ErrorMessage", MB_OK);
		Logger::Log( t_Message, "TextureResourceLoadSave", LoggerType::MSG_ERROR );
		return nullptr;
	}
	else
	{
		Texture* t_NewTexture = new Texture();
		t_NewTexture->SetTextureView(t_NewSRV);
		t_NewTexture->SetName(p_FileName);
		return t_NewTexture;
	}
}

void TextureResourceLoadSave::Save(Resource* p_File)
{
	std::string p_FileName = p_File->GetName();
	//std::wstring t_LoadTextString = std::wstring(p_FileName.begin(), p_FileName.end());
	//std::wstring t_Message = L"Can't save textures, regarding " + t_LoadTextString;
	//MessageBox(nullptr, t_Message.c_str(), L"ErrorMessage", MB_OK);
	Logger::Log( "Can't save textures, regarding " + p_FileName, "TextureResourceLoadSave", LoggerType::MSG_ERROR );
}

const char* TextureResourceLoadSave::GetExtension()
{
	return ".dds";
}
