#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	glm::vec3 position;		//位置
	glm::vec3 forward;		//朝向z-
	glm::vec3 right;		//右方向x+
	glm::vec3 up;			//上方向y+
	glm::vec3 worldUp;		//世界坐标系y+

	float pitch;	//仰角
	float yaw;		//转向角

	float sensitivityX = 0.01f, sensitivityY = 0.01f;	//灵敏度

	glm::vec3 speed;

	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="position">相机位置</param>
	/// <param name="target">LookAt目标位置</param>
	/// <param name="wordUp">世界y+</param>
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 wordlUp);

	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="position">相机位置</param>
	/// <param name="pitch">forward与水平面夹角</param>
	/// <param name="yaw">forward与z-夹角</param>
	/// <param name="worldUp">世界y+</param>
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);

	/// <summary>
	/// 返回视图变换矩阵View
	/// </summary>
	/// <returns></returns>
	glm::mat4 getViewMatrix();

	/// <summary>
	/// 处理鼠标移动
	/// </summary>
	/// <param name="deltaX">x坐标增量</param>
	/// <param name="deltaY">y坐标增量</param>
	void processMouseMovement(float deltaX, float deltaY);

	/// <summary>
	/// 更新相机位置
	/// </summary>
	void updatePoistion();
private:
	int moveMode = 0;	//相机移动模式 0自由FPS  1固定

	/// <summary>
	/// 更新相机的向量
	/// </summary>
	void updateVectors();
};

