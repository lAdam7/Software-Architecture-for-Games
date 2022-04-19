#pragma once

class Mouse
{
private:
	float sensitivity = 4.0f;
	float mouseX = 0.0f;
	float mouseY = 0.0f;
	float tolerance = 0.3f;
	float widthRadius;
public:
	void StartUp();
	void UpdateMouse();
};
