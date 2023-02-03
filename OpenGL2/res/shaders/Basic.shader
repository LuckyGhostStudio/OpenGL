#shader vertex
#version 330 core

layout(location = 0) in vec4 position;	//位置
layout(location = 1) in vec2 texCoord;	//纹理坐标

//输出到片元着色器
out vec2 v_TexCoord;

uniform mat4 u_MVP;		//模型视图投影矩阵

void main()
{
	gl_Position = u_MVP * position;	//顶点位置做MVP变换
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//从顶点着色器输入
in vec2 v_TexCoord;

//从主程序输入
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);	//在纹理u_Texture的texCoord坐标取色
	color = texColor;
};