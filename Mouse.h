#pragma once

class Mouse
{
private:
	float m_sensitivity = 4.0f;
	float m_mouseX = 0.0f;
	float m_mouseY = 0.0f;
	float m_tolerance = 0.3f;
	float m_widthRadius = 2000.0f;
public:
	void StartUp();
	void UpdateMouse();
};