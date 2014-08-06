#include "FontEngine.h"


FontEngine::FontEngine()
{
	m_FontType = nullptr;
	m_Texture = nullptr;
}


FontEngine::~FontEngine()
{
}

void FontEngine::Release()
{
	//m_Texture->Release();
	if (m_Texture)
	{
		delete(m_Texture);
		m_Texture = nullptr;
	}
	ReleaseFont();
}

void FontEngine::ReleaseFont()
{
	if (m_FontType)
	{
		delete[] m_FontType;
		m_FontType = nullptr;
	}
}

bool FontEngine::Init(ID3D11Device* p_Device, char* p_FontFileName, std::wstring p_TextureFileName)
{
	bool t_Result;

	t_Result = LoadFontData(p_FontFileName);
	if (!t_Result)
	{
		MessageBox(nullptr,L"Font could not be loaded",L"Error",MB_ICONERROR | MB_OK);
		return false;
	}

	//Loading texture
	/*if (m_Texture->LoadTexture(p_Device, p_TextureFileName) != true)
		return false;*/
	return true;
}

bool FontEngine::LoadFontData(char* p_FileName)
{
	std::ifstream t_Read;
	char t_Data;
	//Font spacing buffer
	m_FontType = new FontType[95];
	if (!m_FontType)
	{
		return false;
	}
	t_Read.open(p_FileName);
	if (t_Read.fail())
		return false;

	//Reading the 95 characters
	for (int i = 0; i < 95; i++)
	{
		t_Read.get(t_Data);
		while (t_Data != ' ')
		{
			t_Read.get(t_Data);
		}
		t_Read.get(t_Data);
		while (t_Data != ' ')
		{
			t_Read.get(t_Data);
		}

		t_Read >> m_FontType[i].left;
		t_Read >> m_FontType[i].right;
		t_Read >> m_FontType[i].size;
	}


	t_Read.close();
	return true;
}

void FontEngine::BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY)
{
	VertexType* t_Vertex;
	int t_NumLetters;
	int t_Index; 
	int t_Letter;

	//vertextype-structure
	t_Vertex = (VertexType*)vertices;
	//number of letters in the current sentence
	t_NumLetters = (int)strlen(sentence);

	t_Index = 0;
	//Iterating through every letter -> to make a quad

	for (int i = 0; i < t_NumLetters; i++)
	{
		t_Letter = ((int)sentence[i]) - 32;
		//make sure to move some pixels if this(letter) is just a space

		if (t_Letter == 0)
		{
			drawX = drawX + 3.0f;
		}

		else
		{
			//QUAD

				//Triangle 1
			t_Vertex[t_Index].position = XMFLOAT3(drawX , drawY, 0.0f);//Top left
			t_Vertex[t_Index].texture = XMFLOAT2(m_FontType[t_Letter].left, 0.0f);
			t_Index += 1;

			t_Vertex[t_Index].position = XMFLOAT3(drawX + m_FontType[t_Letter].size, (drawY-16), 0.0f);//Bottom left
			t_Vertex[t_Index].texture = XMFLOAT2(m_FontType[t_Letter].right, 1.0f);
			t_Index += 1;

			t_Vertex[t_Index].position = XMFLOAT3(drawX, (drawY - 16), 0.0f);//Bottom left
			t_Vertex[t_Index].texture = XMFLOAT2(m_FontType[t_Letter].left, 1.0f);
			t_Index += 1;

			/////////////
				//Triangle2
			t_Vertex[t_Index].position = XMFLOAT3(drawX, drawY, 0.0f);//Top left
			t_Vertex[t_Index].texture = XMFLOAT2(m_FontType[t_Letter].left, 0.0f);
			t_Index += 1;

			t_Vertex[t_Index].position = XMFLOAT3(drawX + m_FontType[t_Letter].size, drawY, 0.0f);//Top right
			t_Vertex[t_Index].texture = XMFLOAT2(m_FontType[t_Letter].right, 0.0f);
			t_Index += 1;

			t_Vertex[t_Index].position = XMFLOAT3(drawX + m_FontType[t_Letter].size, (drawY-16), 0.0f);//Bottom right
			t_Vertex[t_Index].texture = XMFLOAT2(m_FontType[t_Letter].right, 1.0f);
			t_Index += 1;

			//Update the x position after each letter (by the size of the letter and one pixel)
			drawX = drawX + m_FontType[t_Letter].size + 1.0f;
		}
	}
	return;
}