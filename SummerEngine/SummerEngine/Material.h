#pragma once
#include "Resource.h"
#include <vector>
#include "Texture.h"

class Material:Resource
{
public:
	Material();
	~Material();

	virtual const std::string &GetName() const;
	virtual const ResourceType GetType() const;

private:
	std::vector<Texture*> m_Textures;
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
