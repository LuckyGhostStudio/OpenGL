#version 330 core			
//in vec4 vertexColor;
//�������
in vec3 fragPos;	//ƬԪλ��
in vec3 normal;		//������
in vec2 texCoord;	//��������

struct Material
{
	sampler2D diffuseTex;	//��������ͼ
	sampler2D specularTex;	//���淴����ͼ
	float shininess;		//�߹�ǿ��	Խ��߹ⷶΧԽС
};

//ƽ�й�
struct DirectionalLight
{
	vec3 color;		//��ɫ
	vec3 direction;	//���䷽��
};

//���Դ
struct PointLight
{
	vec3 position;	//λ��
	vec3 color;		//��ɫ
	float constant;
	float linear;
	float quadratic;
};

//�۹�Դ
struct SpotLight
{
	vec3 position;		//λ��
	vec3 color;			//��ɫ
	vec3 direction;		//���䷽��
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

//���ⲿ����Shader�ı���
uniform vec3 objectColor;		//������ɫ
uniform vec3 ambientColor;		//��������ɫ 
uniform vec3 cameraPos;			//�����ɫ

//�������
out vec4 fragColor;		//ƬԪ��ɫ

//����ƽ�й���
vec3 calculateDirectionalLight(DirectionalLight light, vec3 cameraDir)
{
	vec3 resultColor;

	//��������ɫ
	float diffuseIntensity = max(dot(-light.direction, normal), 0);			//������ǿ�� [0, 1]
	vec3 diffuseTexColor = texture(material.diffuseTex, texCoord).rgb;		//ȡ��������ͼ��texCoord�����rgbֵ
	vec3 diffuseColor = diffuseTexColor * diffuseIntensity * light.color;	//��������ɫ = ��������ͼ��ɫ * ������ǿ�� * �ƹ���ɫ

	//���淴����ɫ
	vec3 reflectDir = reflect(light.direction, normal);										//����ⷽ��
	float specularIntensity = pow(max(dot(reflectDir, cameraDir), 0), material.shininess);	//���淴��ǿ�� [0, 1]
	vec3 specularTexColor = texture(material.specularTex, texCoord).rgb;					//���淴����ɫ
	vec3 specularColor = specularIntensity * specularTexColor * light.color;				//���淴����ɫ = ���淴����ͼ��ɫ * ���淴��ǿ�� * �ƹ���ɫ
	//��������ɫ
	vec3 ambientColor = diffuseTexColor * ambientColor;

	resultColor = ambientColor + diffuseColor + specularColor;

	return resultColor;
}

//������Դ����
vec3 calculatePointLight(PointLight light,vec3 cameraDir)
{
	vec3 resultColor;

	vec3 lightDir = normalize(light.position - fragPos);			//ָ���Դ

	float dist = length(light.position - fragPos);														//��Դ��ƬԪ�ľ���
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));	//��Դǿ��˥��ϵ��
	light.color = attenuation * light.color;															//�ƹ�ǿ��˥��

	//��������ɫ
	float diffuseIntensity = max(dot(lightDir, normal), 0);					//������ǿ�� [0, 1]
	vec3 diffuseTexColor = texture(material.diffuseTex, texCoord).rgb;		//ȡ��������ͼ��texCoord�����rgbֵ
	vec3 diffuseColor = diffuseTexColor * diffuseIntensity * light.color;	//��������ɫ = ��������ͼ��ɫ * ������ǿ�� * �ƹ���ɫ

	//���淴����ɫ
	vec3 reflectDir = reflect(-lightDir, normal);											//����ⷽ��
	float specularIntensity = pow(max(dot(reflectDir, cameraDir), 0), material.shininess);	//���淴��ǿ�� [0, 1]
	vec3 specularTexColor = texture(material.specularTex, texCoord).rgb;					//���淴����ɫ
	vec3 specularColor = specularIntensity * specularTexColor * light.color;				//���淴����ɫ = ���淴����ͼ��ɫ * ���淴��ǿ�� * �ƹ���ɫ
	
	//��������ɫ
	vec3 ambientColor = diffuseTexColor * ambientColor;

	resultColor = ambientColor + diffuseColor + specularColor;

	return resultColor;
}

//�۹��
vec3 calculateSpotLight(SpotLight light, vec3 cameraDir)
{
	vec3 resultColor;

	vec3 lightDir = normalize(light.position - fragPos);			//ָ���Դ

	float dist = length(light.position - fragPos);														//��Դ��ƬԪ�ľ���
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));	//��Դǿ��˥��ϵ��
	light.color = attenuation * light.color;															//�ƹ�ǿ��˥��

	//����۹�Ч��
	float cosTheta = dot(-lightDir, light.direction);	//ָ���ƬԪ�Ĺ��� �� SpotLight���� �нǵ� cos
	float spotRatio;									//�۹����
	float cosAngleInner = cos(spotLight.angleInner);	//���Ž�����
	float cosAngleOutter = cos(spotLight.angleOutter);	//���Ž�����

	if(cosTheta > cosAngleInner){	//��SpotLight���Ž���	 ��
		spotRatio = 1.0f;
	}
	else if(cosTheta > cosAngleOutter){	//�����Ž��� ��
		spotRatio = (cosTheta - cosAngleOutter) / (cosAngleInner - cosAngleOutter);		//��inner��outter���Լ�С
	}
	else{	//�����Ž��� ��
		spotRatio = 0.0f;
	}

	light.color = light.color * spotRatio;		//����۹�Ч��

	//��������ɫ
	float diffuseIntensity = max(dot(lightDir, normal), 0);					//������ǿ�� [0, 1]
	vec3 diffuseTexColor = texture(material.diffuseTex, texCoord).rgb;		//ȡ��������ͼ��texCoord�����rgbֵ
	vec3 diffuseColor = diffuseTexColor * diffuseIntensity * light.color;	//��������ɫ = ��������ͼ��ɫ * ������ǿ�� * �ƹ���ɫ

	//���淴����ɫ
	vec3 reflectDir = reflect(-lightDir, normal);											//����ⷽ��
	float specularIntensity = pow(max(dot(reflectDir, cameraDir), 0), material.shininess);	//���淴��ǿ�� [0, 1]
	vec3 specularTexColor = texture(material.specularTex, texCoord).rgb;					//���淴����ɫ
	vec3 specularColor = specularIntensity * specularTexColor * light.color;				//���淴����ɫ = ���淴����ͼ��ɫ * ���淴��ǿ�� * �ƹ���ɫ
	
	//��������ɫ
	vec3 ambientColor = diffuseTexColor * ambientColor;

	resultColor = ambientColor + diffuseColor + specularColor;

	return resultColor;
}

void main()
{				
	vec3 cameraDir = normalize(cameraPos - fragPos);		//ָ���������

	vec3 resultColor;

	resultColor += calculateDirectionalLight(directionalLight, cameraDir);	//ƽ�й���
	resultColor += calculatePointLight(pointLight, cameraDir);				//���Դ
	resultColor += calculateSpotLight(spotLight, cameraDir);				//�۹��
	resultColor += ambientColor;

	fragColor = vec4(resultColor * objectColor, 1.0f);
}