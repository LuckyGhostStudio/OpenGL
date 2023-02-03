#version 330 core			
//in vec4 vertexColor;
//输入变量
in vec3 fragPos;	//片元位置
in vec3 normal;		//法向量
in vec2 texCoord;	//纹理坐标

struct Material
{
	sampler2D diffuseTex;	//漫反射贴图
	sampler2D specularTex;	//镜面反射贴图
	float shininess;		//高光强度	越大高光范围越小
};

//平行光
struct DirectionalLight
{
	vec3 color;		//颜色
	vec3 direction;	//照射方向
};

//点光源
struct PointLight
{
	vec3 position;	//位置
	vec3 color;		//颜色
	float constant;
	float linear;
	float quadratic;
};

//聚光源
struct SpotLight
{
	vec3 position;		//位置
	vec3 color;			//颜色
	vec3 direction;		//照射方向
	float constant;
	float linear;
	float quadratic;
	float angleInner;
	float angleOutter;
};

uniform Material material;

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

//从外部传入Shader的变量
uniform vec3 objectColor;		//物体颜色
uniform vec3 ambientColor;		//环境光颜色 
uniform vec3 cameraPos;			//相机颜色

//输出变量
out vec4 fragColor;		//片元颜色

//计算平行光照
vec3 calculateDirectionalLight(DirectionalLight light, vec3 cameraDir)
{
	vec3 resultColor;

	//漫反射颜色
	float diffuseIntensity = max(dot(-light.direction, normal), 0);			//漫反射强度 [0, 1]
	vec3 diffuseTexColor = texture(material.diffuseTex, texCoord).rgb;		//取漫反射贴图在texCoord坐标的rgb值
	vec3 diffuseColor = diffuseTexColor * diffuseIntensity * light.color;	//漫反射颜色 = 漫反射贴图颜色 * 漫反射强度 * 灯光颜色

	//镜面反射颜色
	vec3 reflectDir = reflect(light.direction, normal);										//反射光方向
	float specularIntensity = pow(max(dot(reflectDir, cameraDir), 0), material.shininess);	//镜面反射强度 [0, 1]
	vec3 specularTexColor = texture(material.specularTex, texCoord).rgb;					//镜面反射颜色
	vec3 specularColor = specularIntensity * specularTexColor * light.color;				//镜面反射颜色 = 镜面反射贴图颜色 * 镜面反射强度 * 灯光颜色
	//环境光颜色
	vec3 ambientColor = diffuseTexColor * ambientColor;

	resultColor = ambientColor + diffuseColor + specularColor;

	return resultColor;
}

//计算点光源光照
vec3 calculatePointLight(PointLight light,vec3 cameraDir)
{
	vec3 resultColor;

	vec3 lightDir = normalize(light.position - fragPos);			//指向光源

	float dist = length(light.position - fragPos);														//光源距片元的距离
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));	//光源强度衰减系数
	light.color = attenuation * light.color;															//灯光强度衰减

	//漫反射颜色
	float diffuseIntensity = max(dot(lightDir, normal), 0);					//漫反射强度 [0, 1]
	vec3 diffuseTexColor = texture(material.diffuseTex, texCoord).rgb;		//取漫反射贴图在texCoord坐标的rgb值
	vec3 diffuseColor = diffuseTexColor * diffuseIntensity * light.color;	//漫反射颜色 = 漫反射贴图颜色 * 漫反射强度 * 灯光颜色

	//镜面反射颜色
	vec3 reflectDir = reflect(-lightDir, normal);											//反射光方向
	float specularIntensity = pow(max(dot(reflectDir, cameraDir), 0), material.shininess);	//镜面反射强度 [0, 1]
	vec3 specularTexColor = texture(material.specularTex, texCoord).rgb;					//镜面反射颜色
	vec3 specularColor = specularIntensity * specularTexColor * light.color;				//镜面反射颜色 = 镜面反射贴图颜色 * 镜面反射强度 * 灯光颜色
	
	//环境光颜色
	vec3 ambientColor = diffuseTexColor * ambientColor;

	resultColor = ambientColor + diffuseColor + specularColor;

	return resultColor;
}

//聚光灯
vec3 calculateSpotLight(SpotLight light, vec3 cameraDir)
{
	vec3 resultColor;

	vec3 lightDir = normalize(light.position - fragPos);			//指向光源

	float dist = length(light.position - fragPos);														//光源距片元的距离
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));	//光源强度衰减系数
	light.color = attenuation * light.color;															//灯光强度衰减

	//计算聚光效果
	float cosTheta = dot(-lightDir, light.direction);	//指向该片元的光线 与 SpotLight方向 夹角的 cos
	float spotRatio;									//聚光比率
	float cosAngleInner = cos(spotLight.angleInner);	//内张角余弦
	float cosAngleOutter = cos(spotLight.angleOutter);	//外张角余弦

	if(cosTheta > cosAngleInner){	//在SpotLight内张角内	 内
		spotRatio = 1.0f;
	}
	else if(cosTheta > cosAngleOutter){	//在外张角内 中
		spotRatio = (cosTheta - cosAngleOutter) / (cosAngleInner - cosAngleOutter);		//从inner到outter线性减小
	}
	else{	//在外张角外 外
		spotRatio = 0.0f;
	}

	light.color = light.color * spotRatio;		//计算聚光效果

	//漫反射颜色
	float diffuseIntensity = max(dot(lightDir, normal), 0);					//漫反射强度 [0, 1]
	vec3 diffuseTexColor = texture(material.diffuseTex, texCoord).rgb;		//取漫反射贴图在texCoord坐标的rgb值
	vec3 diffuseColor = diffuseTexColor * diffuseIntensity * light.color;	//漫反射颜色 = 漫反射贴图颜色 * 漫反射强度 * 灯光颜色

	//镜面反射颜色
	vec3 reflectDir = reflect(-lightDir, normal);											//反射光方向
	float specularIntensity = pow(max(dot(reflectDir, cameraDir), 0), material.shininess);	//镜面反射强度 [0, 1]
	vec3 specularTexColor = texture(material.specularTex, texCoord).rgb;					//镜面反射颜色
	vec3 specularColor = specularIntensity * specularTexColor * light.color;				//镜面反射颜色 = 镜面反射贴图颜色 * 镜面反射强度 * 灯光颜色
	
	//环境光颜色
	vec3 ambientColor = diffuseTexColor * ambientColor;

	resultColor = ambientColor + diffuseColor + specularColor;

	return resultColor;
}

void main()
{				
	vec3 cameraDir = normalize(cameraPos - fragPos);		//指向相机方向

	vec3 resultColor;

	resultColor += calculateDirectionalLight(directionalLight, cameraDir);	//平行光照
	resultColor += calculatePointLight(pointLight, cameraDir);				//点光源
	resultColor += calculateSpotLight(spotLight, cameraDir);				//聚光灯
	resultColor += ambientColor;

	fragColor = vec4(resultColor * objectColor, 1.0f);
}