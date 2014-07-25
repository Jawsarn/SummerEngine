#include "TextureResourceLoadSave.h"
#include "DDSTextureLoader.h"


Resource* TextureResourceLoadSave::Load(std::string p_FileName)
{
	
	return nullptr;
}

void TextureResourceLoadSave::Save(Resource* p_File)
{
	
	//if (FAILED(hr))
	//{
	//	MessageBox(nullptr, L"Can't save textures stupied.", L"ErrorMessage", MB_OK);
	//	return hr;
	//}
}

const char* TextureResourceLoadSave::GetExtension()
{
	return ".dds";
}
