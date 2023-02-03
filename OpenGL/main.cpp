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

//ʮ��Cubeλ��
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
//Camera mainCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));	//�������
Camera mainCamera(glm::vec3(0, 0, -10.0f), 0.0f, 0.0f, glm::vec3(0, 1.0f, 0));	//�������
#pragma endregion

#pragma region Light Declare
DirectionalLight lightD(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(35.0f, 25.0f, 0), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f);
PointLight lightP(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0), glm::vec3(1.0f, 0.0f, 0.0f), 3.0f);
SpotLight lightS(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(90.0f, 0, 0), glm::vec3(0.0f, 0.0f, 1.0f), 5.0f);
#pragma endregion

#pragma region Input Declare

float lastMouseX, lastMouseY;	//����ϴ�λ��
bool firstMouseOn = true;		//����һ�ν���

/// <summary>
/// ��������
/// </summary>
/// <param name="window">���봰��</param>
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {	//��window���ڰ��¿ո�
		glfwSetWindowShouldClose(window, true);					//�ر�window����
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, 0, 1.0f);	//��ǰ
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, 0, -1.0f);	//���
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(-1.0f, 0, 0);	//����
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(1.0f, 0, 0);	//����
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, 1.0f, 0);	//����
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		mainCamera.speed = glm::vec3(0, -1.0f, 0);	//����
	}
	else {
		mainCamera.speed = glm::vec3(0, 0, 0);
	}
}

/// <summary>
/// ���ص�����
/// </summary>
/// <param name="window">����</param>
/// <param name="xPos">���x����</param>
/// <param name="yPos">���y����</param>
void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouseOn) {
		lastMouseX = xPos;
		lastMouseY = yPos;
		firstMouseOn = false;
	}

	//���λ������
	float deltaX = xPos - lastMouseX;
	float deltaY = yPos - lastMouseY;

	//�����ϴ�λ��
	lastMouseX = xPos;
	lastMouseY = yPos;

	mainCamera.processMouseMovement(deltaX, deltaY);
}

#pragma endregion

/// <summary>
/// ��������
/// </summary>
/// <param name="imagePath">ͼƬ·��</param>
/// <param name="internalFormat">�����е���ɫ��ʽ</param>
/// <param name="format">�������ݵ���ɫ��ʽ</param>
/// <param name="textureSlot">��������Ԫ��</param>
/// <returns>������id</returns>
//unsigned int loadTexture(const char* imagePath, GLint internalFormat, GLenum format, int textureSlot)
//{
//	//����
//	unsigned int textureBuffer;		//������
//	glGenTextures(1, &textureBuffer);
//	glActiveTexture(GL_TEXTURE0 + textureSlot);		//��������Ԫ0+ƫ����
//	glBindTexture(GL_TEXTURE_2D, textureBuffer);
//
//	stbi_set_flip_vertically_on_load(true);	//��תy��
//	int width, height, nrChannel;	//ͼƬ�������� �� ͨ������r g b a��
//	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannel, 0);	//����ͼƬ
//
//	if (data) {	//���سɹ�
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);	//��������
//		glGenerateMipmap(GL_TEXTURE_2D);	//����mipmap
//	}
//	else {
//		cout << "load image failed." << endl;
//	}
//	stbi_image_free(data);	//�ͷ�data����
//
//	return textureBuffer;
//}

/// <summary>
/// ������
/// </summary>
/// <param name="argc">�����в�������</param>
/// <param name="argv">�����е����в���</param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	std::string exePath = argv[0];	//��ǰ��ִ�г���·��
	//std::cout << exePath.substr(0, exePath.find_last_of('\\')) + "\\Models\\nanosuit.obj" << std::endl;

#pragma region Open Window
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);		//��������
	if (!window)	//����Ϊ�� ����ʧ��
	{
		glfwTerminate();	//��ֹ���ڣ�������Դ��
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//���ع��
	glfwSetCursorPosCallback(window, mouseCallback);	//�������ص�����

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {	//glew��ʼ��ʧ��
		std::cout << "Error!" << std::endl;
		glfwTerminate();	//��ֹ���ڣ�������Դ��
		return -1;
	}

	glViewport(0, 0, 800, 600);	//������Ⱦ���ڴ�С
	//glEnable(GL_CULL_FACE);		//�޳���
	//glCullFace(GL_BACK);		//����
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//�߿�ģʽ
	glEnable(GL_DEPTH_TEST);	//������Ȳ���
#pragma endregion

#pragma region Init Shader
	Shader* shader = new Shader("vertexShaderSource.vert", "fragmentShaderSource.frag");
#pragma endregion

#pragma region Init Material
	//Material* material = new Material(shader, 
	//	loadTexture("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),			//��������ͼid 
	//	loadTexture("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),	//���淴����ͼid
	//	32.0f);
#pragma endregion

#pragma region Init and Load Models to VAO, VBO
	//Mesh cube(vertices);
	Model nanosuit(exePath.substr(0, exePath.find_last_of('\\')) + "\\Models\\nanosuit.obj");

	//unsigned int VAO;				//�����������id
	//glGenVertexArrays(1, &VAO);		//����һ��VAO��������VAO��ַ��
	//glBindVertexArray(VAO);			//��VAO����ǰContext
	//
	//unsigned int VBO;																//���㻺�����id
	//glGenBuffers(1, &VBO);															//����VBO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);												//��VBO��VAO �� Array Buffer
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//�����ݵ�VBO
	//
	////unsigned int EBO;																//�����������id
	////glGenBuffers(1, &EBO);															//����EBO
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);										//��EBO��
	////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//���������ݵ�EBO
	//
	////λ������
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	//0�ŵĶ������ԣ�ÿ����������ݵĸ���Ϊ3�������������ݵ�����float���Ƿ��һ������false��һ������ռ�е����ֽ�����λ����ʼƫ����
	//glEnableVertexAttribArray(0);	//����0�Ŷ�������
	////��ɫ����
	////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	//1�ŵĶ������ԣ�ÿ����������ݵĸ���Ϊ3�������������ݵ�����float���Ƿ��һ������false��һ������ռ�е����ֽ�������ɫ������ʼƫ����
	////glEnableVertexAttribArray(1);	//����1�Ŷ�������
	////��������
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	////������������
	//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(3);
#pragma endregion

#pragma region Init and Load Textures
	//unsigned int textureBuffer1 = loadTexture("container.jpg", GL_RGB, GL_RGB, 0);
	//unsigned int textureBuffer2 = loadTexture("face.png", GL_RGBA, GL_RGBA, 1);
#pragma endregion

#pragma region Set MVP Matrices

	glm::mat4 modelMat;			//ģ�ͱ任���� M
	glm::mat4 viewMat;			//��ͼ�任���󣨱任��������꣩V
	glm::mat4 projectionMat;	//ͶӰ���� P
	projectionMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);	//͸��ͶӰ ��ֱ�����Ž� ��Ļ��߱� ���ü�ƽ�� Զ�ü�ƽ��

#pragma endregion

	while (!glfwWindowShouldClose(window))		//���رմ���windowʱ ��Ⱦѭ��
	{
		//��������
		processInput(window);

		//����
		glClearColor(0.275f, 0.275f, 0.275f, 1.0f);					//������ɫ��r,g,b,a��
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			//�����ɫ������ �����Ȼ�����

		viewMat = mainCamera.getViewMatrix();	//������ͼ�任����

		for (int i = 0; i < 1; i++) {
			//���� Model Matrix
			//modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);	//�Ե�λ�������cubeλ�ý���λ��

			//���� View and Projection Matrices if you want

			//���� Material -> Shader Program
			shader->use();

			//���� Material -> Texture
			//glActiveTexture(GL_TEXTURE0 + Shader::DIFFUSE);
			//glBindTexture(GL_TEXTURE_2D, material->diffuseTex);
			//glActiveTexture(GL_TEXTURE0 + Shader::SPECULAR);
			//glBindTexture(GL_TEXTURE_2D, material->specularTex);

			//���� Material -> Uniform����
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
			
			glUniform3f(glGetUniformLocation(shader->ID, "objectColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(shader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			
			//ƽ�й�
			glUniform3f(glGetUniformLocation(shader->ID, "directionalLight.color"), lightD.color.x, lightD.color.y, lightD.color.z);
			glUniform3f(glGetUniformLocation(shader->ID, "directionalLight.direction"), lightD.direction.x, lightD.direction.y, lightD.direction.z);
			
			//���Դ
			glUniform3f(glGetUniformLocation(shader->ID, "pointLight.position"), lightP.position.x, lightP.position.y, lightP.position.z);
			glUniform3f(glGetUniformLocation(shader->ID, "pointLight.color"), lightP.color.x, lightP.color.y, lightP.color.z);
			glUniform1f(glGetUniformLocation(shader->ID, "pointLight.constant"), lightP.constant);
			glUniform1f(glGetUniformLocation(shader->ID, "pointLight.linear"), lightP.linear);
			glUniform1f(glGetUniformLocation(shader->ID, "pointLight.quadratic"), lightP.quadratic);
			
			//�۹��
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

			//���� Model
			//glBindVertexArray(VAO);

			//����������
			//glDrawArrays(GL_TRIANGLES, 0, 36);

			//cube.draw(material->shader);
			nanosuit.draw(shader);
		}

		//׼���´�ѭ��
		glfwSwapBuffers(window);				//����˫���壨ǰ�󻺳�����
		glfwPollEvents();						//��ȡ����
		mainCamera.updatePoistion();			//�������λ��
	}

	glfwTerminate();	//����
	return 0;
}