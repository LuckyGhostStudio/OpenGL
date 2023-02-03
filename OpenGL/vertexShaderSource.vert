#version 330 core									  
layout(location = 0) in vec3 aPos;			//VAO 0����λ λ��
layout(location = 1) in vec3 aNormal;		//VAO 1����λ ������
layout(location = 2) in vec2 aTexCoord;		//VAO 2����λ ��������

//���ⲿ����Shader�ı���
uniform mat4 modelMat;		   //ģ�ͱ任����	M
uniform mat4 viewMat;		   //��ͼ�任���� V
uniform mat4 projectionMat;	   //ͶӰ�任���� P

//�������
out vec3 fragPos;		//ƬԪλ��
out vec3 normal;		//������
out vec2 texCoord;		//��������			

void main(){										  
	gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);		//����λ���� MVP �任
	fragPos = (modelMat * vec4(aPos, 1.0)).xyz;								//ƬԪλ��Ϊ����λ��
	normal = normalize(mat3(transpose(inverse(modelMat))) * aNormal);		//�������� M �任 Mȡ������ת�� ��ֹnormal������ʱ������

	texCoord = aTexCoord;
}