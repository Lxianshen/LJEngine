#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "model.h"

#include <iostream>
#include "EngineEditor.h"

#pragma once
class CommonFunction
{
private:
	// 将其构造和析构成为私有的, 禁止外部构造和析构
	CommonFunction();
	~CommonFunction();

	// 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
	CommonFunction(const CommonFunction& signal);
	const CommonFunction& operator=(const CommonFunction& signal);

	// 唯一单实例对象指针
	static CommonFunction* m_CommonFunction;

public:

	// 获取单实例
	static CommonFunction* GetInstance();

	// 释放单实例，进程退出时调用
	static void deleteInstance();

	//Parameters
	GLFWwindow* window;

	Camera camera;

	void UIRuningMainLoop();
	void CleanupEditorUI();
	void RenderEditorUI();
	//void TransformEditorUI();

	void processInput(GLFWwindow* window);
	//load normal 2d texture
	unsigned int loadTexture(char const* path);
	//load Cube map texture
	unsigned int loadCubemap(vector<std::string> faces);
	GLFWwindow* GetWindow();
	Camera GetCamera();
	EngineEditor engineEditor;

	float GetLastX();
	float GetLastY();
	float GetDeltaTime();
	void SetDeltaTime(float value);
	float GetLastFrame();
	void SetLastFrame(float value);
	float GetSCR_WIDTH();
	float GetSCR_HEIGHT();

};

#endif

