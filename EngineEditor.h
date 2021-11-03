#ifndef ENGINEEDITOR_H
#define ENGINEEDITOR_H

#pragma once
class EngineEditor
{
public:

	EngineEditor();
	~EngineEditor();

	//float* position;
	//float* rotation;
	//float* scale;

	float* GetPosition();
	float* GetRotation();
	float* GetScale();

	void UIRuning();

private:


	void CleanupEditorUI();
	void RenderEditorUI();
	//void TransformEditorUI();

};

#endif
