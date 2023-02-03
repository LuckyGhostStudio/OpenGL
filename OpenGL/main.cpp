#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#define GLEW_STATIC

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Mesh.h"
#include "Model.h"

#include "Camera.h"

using namespace std;

#pragma region Model Data

//十个Cube位置
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

#pragma endregion 

#pragma region Camera Declare
//Camera mainCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));	//主摄像机
Camera mainCamera(glm::vec3(0, 0, -10.0f), 0.0f, 0.0f, glm::vec3(0, 1.0f, 0));	//主摄像机
#pragma endregion

#pragma region Light Declare
DirectionalLight lightD(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(35.0f, 25.0f, 0), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
PointLight lightP(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0), glm::vec3(1.0f, 0.0f, 0.0f), 3.0f);
SpotLight lightS(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(90.0f, 0, 0), glm::vec3(0.0f, 0.0f, 1.0f), 5.0f);
#pragma endregion

#pragma region Input Declare

float lastMouseX, lastMouseY;	//鼠标上次位置
bool firstMouseOn = true;		//鼠标第一次进入

/// <summary>
/// 处理输入
/// </summary>
/// <param name="window">输入窗口</param>
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {	//在window窗口按下空格
		glfwSetWindowShouldClose(window, true);					//关闭window窗口
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, 0, 1.0f);	//向前
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, 0, -1.0f);	//向后
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(-1.0f, 0, 0);	//向左
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(1.0f, 0, 0);	//向右
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, 1.0f, 0);	//向上
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, -1.0f, 0);	//向下
	}
	else {
		mainCamera.speed = glm::vec3(0, 0, 0);
	}
}

/// <summary>
/// 鼠标回调函数
/// </summary>
/// <param name="window">窗口</param>
/// <param name="xPos">鼠标x坐标</param>
/// <param name="yPos">鼠标y坐标</param>
void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouseOn) {
		lastMouseX = xPos;
		lastMouseY = yPos;
		firstMouseOn = false;
	}

	//鼠标位置增量
	float deltaX = xPos - lastMouseX;
	float deltaY = yPos - lastMouseY;

	//更新上次位置
	lastMouseX = xPos;
	lastMouseY = yPos;

	mainCamera.processMouseMovement(deltaX, deltaY);
}

#pragma endregion

/// <summary>
/// 加载纹理
/// </summary>
/// <param name="imagePath">图片路径</param>
/// <param name="internalFormat">纹理中的颜色格式</param>
/// <param name="format">像素数据的颜色格式</param>
/// <param name="textureSlot">激活纹理单元号</param>
/// <returns>纹理缓存id</returns>
//unsigned int loadTexture(const char* imagePath, GLint internalFormat, GLenum format, int textureSlot)
//{
//	//纹理
//	unsigned int textureBuffer;		//纹理缓存
//	glGenTextures(1, &textureBuffer);
//	glActiveTexture(GL_TEXTURE0 + textureSlot);		//激活纹理单元0+偏移量
//	glBindTexture(GL_TEXTURE_2D, textureBuffer);
//
//	stbi_set_flip_vertically_on_load(true);	//翻转y轴
//	int width, height, nrChannel;	//图片参数：宽 高 通道数（r g b a）
//	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannel, 0);	//加载图片
//
//	if (data) {	//加载成功
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);	//生成纹理
//		glGenerateMipmap(GL_TEXTURE_2D);	//产生mipmap
//	}
//	else {
//		cout << "load image failed." << endl;
//	}
//	stbi_image_free(data);	//释放data数据
//
//	return textureBuffer;
//}

/// <summary>
/// 主函数
/// </summary>
/// <param name="argc">命令行参数个数</param>
/// <param name="argv">命令行的所有参数</param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	std::string exePath = argv[0];	//当前可执行程序路径
	//std::cout << exePath.substr(0, exePath.find_last_of('\\')) + "\\Models\\nanosuit.obj" << std::endl;

#pragma region Open Window
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);		//创建窗口
	if (!window)	//窗口为空 创建失败
	{
		glfwTerminate();	//终止窗口（回收资源）
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//隐藏光标
	glfwSetCursorPosCallback(window, mouseCallback);	//设置鼠标回调函数

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {	//glew初始化失败
		std::cout << "Error!" << std::endl;
		glfwTerminate();	//终止窗口（回收资源）
		return -1;
	}

	glViewport(0, 0, 800, 600);	//设置渲染窗口大小
	//glEnable(GL_CULL_FACE);		//剔除面
	//glCullFace(GL_BACK);		//背面
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//线框模式
	glEnable(GL_DEPTH_TEST);	//开启深度测试
#pragma endregion

#pragma region Init Shader
	Shader* shader = new Shader("vertexShaderSource.vert", "fragmentShaderSource.frag");
#pragma endregion

#pragma region Init Material
	//Material* material = new Material(shader, 
	//	loadTexture("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),			//漫反射贴图id 
	//	loadTexture("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),	//镜面反射贴图id
	//	32.0f);
#pragma endregion

#pragma region Init and Load Models to VAO, VBO
	//Mesh cube(vertices);
	Model nanosuit(exePath.substr(0, exePath.find_last_of('\\')) + "\\Models\\nanosuit.obj");

	//unsigned int VAO;				//顶点数组对象id
	//glGenVertexArrays(1, &VAO);		//产生一个VAO（数量，VAO地址）
	//glBindVertexArray(VAO);			//绑定VAO到当前Context
	//
	//unsigned int VBO;																//顶点缓存对象id
	//glGenBuffers(1, &VBO);															//生成VBO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);												//绑定VBO到VAO 的 Array Buffer
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//绑定数据到VBO
	//
	////unsigned int EBO;																//索引缓存对象id
	////glGenBuffers(1, &EBO);															//生成EBO
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);										//绑定EBO到
	////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//绑定索引数据到EBO
	//
	////位置属性
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	//0号的顶点属性，每个顶点的数据的个数为3，顶点描述数据的类型float，是否归一化数据false，一个顶点占有的总字节数，位置起始偏移量
	//glEnableVertexAttribArray(0);	//启用0号顶点属性
	////颜色属性
	////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//1号的顶点属性，每个顶点的数据的个数为3，顶点描述数据的类型float，是否归一化数据false，一个顶点占有的总字节数，颜色数据起始偏移量
	////glEnableVertexAttribArray(1);	//启用1号顶点属性
	////法线属性
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	////纹理坐标属性
	//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(3);
#pragma endregion

#pragma region Init and Load Textures
	//unsigned int textureBuffer1 = loadTexture("container.jpg", GL_RGB, GL_RGB, 0);
	//unsigned int textureBuffer2 = loadTexture("face.png", GL_RGBA, GL_RGBA, 1);
#pragma endregion

#pragma region Set MVP Matrices

	glm::mat4 modelMat;			//模型变换矩阵 M
	glm::mat4 viewMat;			//视图变换矩阵（变换到相机坐标）V
	glm::mat4 projectionMat;	//投影矩阵 P
	projectionMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);	//透视投影 垂直方向张角 屏幕宽高比 近裁剪平面 远裁剪平面

#pragma endregion

	while (!glfwWindowShouldClose(window))		//不关闭窗口window时 渲染循环
	{
		//处理输入
		processInput(window);

		//清屏
		glClearColor(0.275f, 0.275f, 0.275f, 1.0f);					//清屏颜色（r,g,b,a）
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			//清除颜色缓冲区 清除深度缓冲区

		viewMat = mainCamera.getViewMatrix();	//更新视图变换矩阵

		for (int i = 0; i < 1; i++) {
			//设置 Model Matrix
			//modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);	//对单位矩阵根据cube位置进行位移

			//设置 View and Projection Matrices if you want

			//设置 Material -> Shader Program
			shader->use();

			//设置 Material -> Texture
			//glActiveTexture(GL_TEXTURE0 + Shader::DIFFUSE);
			//glBindTexture(GL_TEXTURE_2D, material->diffuseTex);
			//glActiveTexture(GL_TEXTURE0 + Shader::SPECULAR);
			//glBindTexture(GL_TEXTURE_2D, material->specularTex);

			//设置 Material -> Uniform参数
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
			
			glUniform3f(glGetUniformLocation(shader->ID, "objectColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(shader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			
			//平行光
			glUniform3f(glGetUniformLocation(shader->ID, "directionalLight.color"), lightD.color.x, lightD.color.y, lightD.color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "directionalLight.direction"), lightD.direction.x, lightD.direction.y, lightD.direction.z);
			
			//点光源
			glUniform3f(glGetUniformLocation(shader->ID, "pointLight.position"), lightP.position.x, lightP.position.y, lightP.position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "pointLight.color"), lightP.color.x, lightP.color.y, lightP.color.z);
			glUniform1f(glGetUniformLocation(shader->ID, "pointLight.constant"), lightP.constant);
			glUniform1f(glGetUniformLocation(shader->ID, "pointLight.linear"), lightP.linear);
			glUniform1f(glGetUniformLocation(shader->ID, "pointLight.quadratic"), lightP.quadratic);
			
			//聚光灯
			glUniform3f(glGetUniformLocation(shader->ID, "spotLight.position"), lightS.position.x, lightS.position.y, lightS.position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "spotLight.direction"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			glUniform3f(glGetUniformLocation(shader->ID, "spotLight.color"), lightS.color.x, lightS.color.y, lightS.color.z);
			glUniform1f(glGetUniformLocation(shader->ID, "spotLight.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(shader->ID, "spotLight.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(shader->ID, "spotLight.quadratic"), lightS.quadratic);
			glUniform1f(glGetUniformLocation(shader->ID, "spotLight.angleInner"), lightS.angleInner);
			glUniform1f(glGetUniformLocation(shader->ID, "spotLight.angleOutter"), lightS.angleOutter);

			glUniform3f(glGetUniformLocation(shader->ID, "cameraPos"), mainCamera.position.x, mainCamera.position.y, mainCamera.position.z);

			//material->shader->setUniform("material.diffuse", Shader::DIFFUSE);
			//material->shader->setUniform("material.specular", Shader::SPECULAR);
			//material->shader->setUniform("material.shininess", material->shininess);

			//设置 Model
			//glBindVertexArray(VAO);

			//绘制三角形
			//glDrawArrays(GL_TRIANGLES, 0, 36);

			//cube.draw(material->shader);
			nanosuit.draw(shader);
		}

		//准备下次循环
		glfwSwapBuffers(window);				//交换双缓冲（前后缓冲区）
		glfwPollEvents();						//获取输入
		mainCamera.updatePoistion();			//更新相机位置
	}

	glfwTerminate();	//结束
	return 0;
}