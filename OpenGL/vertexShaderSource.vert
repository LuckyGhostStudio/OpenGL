#version 330 core									  
layout(location = 0) in vec3 aPos;			//VAO 0号栏位 位置
layout(location = 1) in vec3 aNormal;		//VAO 1号栏位 法向量
layout(location = 2) in vec2 aTexCoord;		//VAO 2号栏位 纹理坐标

//从外部传入Shader的变量
uniform mat4 modelMat;		   //模型变换矩阵	M
uniform mat4 viewMat;		   //视图变换矩阵 V
uniform mat4 projectionMat;	   //投影变换矩阵 P

//输出变量
out vec3 fragPos;		//片元位置
out vec3 normal;		//法向量
out vec2 texCoord;		//纹理坐标			

void main(){										  
	gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);		//顶点位置做 MVP 变换
	fragPos = (modelMat * vec4(aPos, 1.0)).xyz;								//片元位置为顶点位置
	normal = normalize(mat3(transpose(inverse(modelMat))) * aNormal);		//法向量做 M 变换 M取逆矩阵的转置 防止normal在缩放时被拉伸

	texCoord = aTexCoord;
}