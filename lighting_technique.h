#ifndef LIGHTINGTECHNIQUE_H
#define LIGHTINGTECHNIQUE_H

#include "technique.h"
#include "math_3d.h"

#define MAX_POINT_LIGHTS 2
#define MAX_SPOT_LIGHTS 2
#define MAX_DIRECTIONAL_LIGHTS 2

struct BaseLight
{
	Vector3f Color;
	float AmbientIntensity;
	float DiffuseIntensity;

	BaseLight()
	{
		Color = Vector3f(0.0f, 0.0f, 0.0f);
		AmbientIntensity = 0.0f;
		DiffuseIntensity = 0.0f;
	}
};

struct DirectionalLight : public BaseLight
{
	Vector3f Direction;

	DirectionalLight()
	{
		Direction = Vector3f(0.0f, 0.0f, 0.0f);
	}
};

struct PointLight : public BaseLight
{
	// в мировых координатах
	Vector3f Position;

	// коэффициенты затухания, постоянный, линейный, эспоненциальный
	struct
	{
		float Constant;
		float Linear;
		float Exp;
	} Attenuation;

	PointLight()
	{
		Position = Vector3f(0.0f, 0.0f, 0.0f);
		Attenuation.Constant = 1.0f;
		Attenuation.Linear = 0.0f;
		Attenuation.Exp = 0.0f;
	}
};

struct SpotLight : public PointLight
{
	Vector3f Direction;
	float Cutoff;

	SpotLight()
	{
		Direction = Vector3f(0.0f, 0.0f, 0.0f);
		Cutoff = 0.0f;
	}
};

class LightingTechnique : public Technique
{
public:
	LightingTechnique();
	virtual bool Init();

	void SetWVP(const Matrix4f* WVP);
	void SetWorldMatrix(const Matrix4f& WorldInverse);
	void SetTextureUnit(unsigned int TextureUnit);
	
	void SetEyeWorldPos(const Vector3f &EyeWorldPos);
	void SetMatSpecularIntensity(float Intensity);
	void SetMatSpecularPower(float Power);

	void SetPointLights(unsigned int NumLights, const PointLight* pLights);
	void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
	void SetDirectionalLights(unsigned int NumLights, const DirectionalLight* pLight);
private:
	GLuint m_WVPLocation;
	GLuint m_WorldMatrixLocation;
	GLuint m_samplerLocation;

	GLuint m_eyeWorldPosLocation;
	GLuint m_matSpecularIntensityLocation;
	GLuint m_matSpecularPowerLocation;
	GLuint m_numPointLightsLocation;
	GLuint m_numSpotLightsLocation;
	GLuint m_numDirectionalLightsLocation;

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint Direction;
		GLuint DiffuseIntensity;
	} m_dirLightsLocation[MAX_DIRECTIONAL_LIGHTS];

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		struct {
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_pointLightsLocation[MAX_POINT_LIGHTS];

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		GLuint Direction;
		GLuint Cutoff;
		struct {
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_spotLightsLocation[MAX_SPOT_LIGHTS];
};

#endif // LIGHTINGTECHNIQUE_H