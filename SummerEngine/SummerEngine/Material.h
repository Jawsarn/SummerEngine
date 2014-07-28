#pragma once
#include "Resource.h"
#include "Texture.h"
#include <map>

class Material:Resource
{
public:
	Material();
	~Material();

	float m_Ns;					//Shininess of the material
	float m_Ka[3];				//Ambient color (r,g,b)
	float m_Kd[3];				//Diffuse color (r,g,b)
	float m_Ks[3];				//Specular color (r,g,b)
	float m_Ni;					//Reflection index
	float m_D;					//Transparency Tr (alpha)
	float m_Tf[3];				//Color Transperancy color (d or Tr)
	float m_Ke;					//Emissive color
	UINT32 m_Illum;				//Define the illumination model: illum = 1 a flat material with no specular highlights, illum = 2 denotes the presence of specular highlights

	std::string m_Map_Kd;		//diffuse
	std::string m_Map_Ka;		//ambient
	std::string m_Map_Ks;		//specular
	std::string m_Map_Ke;		//emissive fucked up shit
	std::string m_Map_Ns;		//specular shinyness
	std::string m_Map_D;		//transparency
	std::string m_Bump;			//normal map
	std::string m_Disp;			//displacment map
	std::string m_Occulsion;	//diffuse blackmap

	std::map<std::string, Texture*>* GetTextures();
	void LoadTextures();

	void SetFileName(std::string p_FileName);

	virtual void SetName(std::string p_Name);
	virtual const std::string GetName();
	virtual const ResourceType GetType() const;

private:
	std::map<std::string, Texture*> m_Textures;

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
