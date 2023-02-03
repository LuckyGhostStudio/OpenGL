#shader vertex
#version 330 core

layout(location = 0) in vec4 position;	//λ��
layout(location = 1) in vec2 texCoord;	//��������

//�����ƬԪ��ɫ��
out vec2 v_TexCoord;

uniform mat4 u_MVP;		//ģ����ͼͶӰ����

void main()
{
	gl_Position = u_MVP * position;	//����λ����MVP�任
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//�Ӷ�����ɫ������
in vec2 v_TexCoord;

//������������
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);	//������u_Texture��texCoord����ȡɫ
	color = texColor;
};