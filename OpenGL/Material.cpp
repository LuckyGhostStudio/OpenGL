#include "Material.h"

Material::Material(Shader* shader, unsigned int diffuseTex, unsigned int specularTex, float shininess)
{
	this->shader = shader;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
	this->shininess = shininess;
}
