#pragma once
#include "Resource.h"
#include <vector>
#include "Texture.h"

class Material:Resource
{
public:
	Material();
	~Material();


	struct MaterialData
	{
		std::string m_Name;			//Material name
		float m_Ns;					//Shininess of the material
		float m_Ka[3];				//Ambient color (r,g,b)
		float m_Kd[3];				//Diffuse color (r,g,b)
		float m_Ks[3];				//Specular color (r,g,b)
		float m_Ni;					//Reflection index
		float m_D;					//Transparency Tr (alpha)
		float m_Tf[3];				//Color Transperancy color (d or Tr)
		float m_Ke;					//Emissive color
		UINT32 m_Illum;				//Define the illumination model: illum = 1 a flat material with no specular highlights, illum = 2 denotes the presence of specular highlights

		std::string m_Map_Kd;
		std::string m_Map_Ka;
		std::string m_Map_Ks;
		std::string m_Map_Ke;
		std::string m_Map_Ns;
		std::string m_Map_D;
		std::string m_Bump;
		std::string m_Disp;
		std::string m_Occulsion;

		MaterialData()
		{
			//Default values
			m_Kd[0] = 0; m_Kd[1] = 0; m_Kd[2] = 0;
			m_Ka[0] = 0; m_Ka[1] = 0; m_Ka[2] = 0;
			m_Tf[0] = 0; m_Tf[1] = 0; m_Tf[2] = 0;
			m_Ks[0] = 0; m_Ks[1] = 0; m_Ks[2] = 0;
			m_Ni = 0;
			m_Ns = 0;
			m_D = 0;
			m_Illum = 0;
			m_Ke = 0;

			m_Name = "None";

			//Textures
			m_Map_Kd = "None";
			m_Map_Ka = "None";
			m_Map_Ks = "None";
			m_Map_Ke = "None";
			m_Map_Ns = "None";
			m_Map_D = "None";
			m_Bump = "None";
			m_Disp = "None";
			m_Occulsion = "None";
		}
	};

	void SetMaterialData(MaterialData* p_MaterialData);
	MaterialData* GetMaterialData();
	std::vector<Texture*> GetTextures();

	virtual const std::string &GetName() const;
	virtual const ResourceType GetType() const;

private:
	std::vector<Texture*> m_Textures;
	MaterialData* m_MaterialData;
};

//struct Diffuse
//{
//	//color-RGB
//	//base-texture
//};
//
//struct BumpedDiffuse
//{
//	//color-RGB
//	//base-texture
//	//normalmap-texture
//};
//
//struct BumpedSpecular
//{
//	//color-RGB
//	//spec color
//	float m_Shininess;
//	//base-texture
//	//normalmap-texture
//};
//
//struct Decal
//{
//	//color-RGB
//	//base-texture
//	//decal-texture
//};
//
//struct DiffuseDetail
//{
//	//color-RGB
//	//base-texture
//	//detail-texture
//};
//
//struct ParrallaxDiffuse
//{
//	//color-RGB
//	float m_Height;
//	//base-texture
//	//normalmap-texture
//	//heightmap-texture
//};
//
//struct ParrallaxSpecular
//{
//	//color-RGB
//	//specular color
//	float m_Shininess;
//	float m_Height;
//	//base-texture
//	//normalmap-texture
//	//heightmap-texture
//};
//
//struct Specular
//{
//	//color-RGB
//	//specular color
//	float m_Shininess;
//	//base texture
//};
//
//struct Paricles
//{
//	struct Additive
//	{
//		//tint color rgb
//		//particle-texture
//		float m_SoftParticleFactor;
//
//	};
//
//	struct AdditiveSoft
//	{
//		//particle-texture
//		float m_SoftParticleFactor;
//
//	};
//
//	struct AlphaBlended
//	{
//		//tint color-RGB
//		//particle-texture
//		float m_SoftParticleFactor;
//
//	};
//
//	struct AlphaBlendedPreMultipply
//	{
//		//particle-texture
//		float m_SoftParticleFactor;
//
//	};
//
//	struct Multiply
//	{
//		//particle-texture
//		float m_SoftParticleFactor;
//
//	};
//
//	struct MultiplyDouble
//	{
//		//particle-texture
//		float m_SoftParticleFactor;
//
//	};
//
//};
//
//struct RenderFX
//{
//	struct Skybox
//	{
//		//tint color
//		//front texture (+z)
//		//back texture (-z)
//		//left texture (+x)
//		//right texture (-x)
//		//up texture (+y)
//		//down texture (-y)
//	};
//
//	struct SkyboxCubed
//	{
//		//tint color
//		//cubemap -texture
//	};
//};
//
//struct FX
//{
//	struct Flare
//	{
//		//particle - texture
//	};
//};
//
//struct Transparent
//{
//	struct Diffuse
//	{
//		//color-RGB
//		//base-texture
//	};
//
//	struct BumpedDiffuse
//	{
//		//color-RGB
//		//base-texture
//		//normalmap-texture
//	};
//
//	struct BumpedSpecular
//	{
//		//color-RGB
//		//spec color
//		float m_Shininess;
//		//base-texture
//		//normalmap-texture
//	};
//
//	struct ParrallaxDiffuse
//	{
//		//color-RGB
//		float m_Height;
//		//base-texture
//		//normalmap-texture
//		//heightmap-texture
//	};
//
//	struct ParrallaxSpecular
//	{
//		//color-RGB
//		//specular color
//		float m_Shininess;
//		float m_Height;
//		//base-texture
//		//normalmap-texture
//		//heightmap-texture
//	};
//};
