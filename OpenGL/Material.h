#pragma once

#include "Shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Material
{
public:
	Shader* shader;
	unsigned int diffuseTex;	//漫反射贴图id
	unsigned int specularTex;	//镜面反贴图id
	float shininess;	//高光强度

	/// <summary>
	/// 材质
	/// </summary>
	/// <param name="shader">着色器</param>
	/// <param name="diffuse">漫反射贴图id</param>
	/// <param name="specular">镜面反射贴图id</param>
	/// <param name="shininess">高光强度</param>
	Material(Shader* shader, unsigned int diffuse, unsigned int specular, float shininess);
};

