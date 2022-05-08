#include "Mouse.h"
#include "myinputs.h"
#include "mydrawengine.h"

void Mouse::UpdateMouse()
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleMouse();

	int xAxis = pInputs->GetMouseDX();
	int yAxis = pInputs->GetMouseDY();

	if (xAxis - m_tolerance > 0 && m_mouseX < (m_widthRadius - 50))
	{
		m_mouseX = m_mouseX + (xAxis * m_sensitivity);
		if (m_mouseX > (m_widthRadius - 50))
			m_mouseX = m_widthRadius - 50;
	}
	else if (xAxis + m_tolerance < 0 && m_mouseX >(-m_widthRadius + 50))
	{
		m_mouseX = m_mouseX - (-xAxis * m_sensitivity);
		if (m_mouseX < (-m_widthRadius + 50))
			m_mouseX = -m_widthRadius + 50;
	}

	if (yAxis + m_tolerance < 0 && m_mouseY < 950)
	{
		m_mouseY = m_mouseY + (-yAxis * m_sensitivity);
		if (m_mouseY > 950)
			m_mouseY = 950;
	}
	else if (yAxis - m_tolerance > 0 && m_mouseY > -950)
	{
		m_mouseY = m_mouseY - (yAxis * m_sensitivity);
		if (m_mouseY < -950)
			m_mouseY = -950;
	}

	Vector2D cameraPos = MyDrawEngine::GetInstance()->theCamera.GetCameraPosition();

	MyDrawEngine::GetInstance()->FillCircle(Vector2D(cameraPos.XValue + m_mouseX, -cameraPos.YValue + m_mouseY), 50.0f, MyDrawEngine::YELLOW);

	MyDrawEngine::GetInstance()->WriteDouble(500, 50, cameraPos.XValue + m_mouseX, MyDrawEngine::RED);
	MyDrawEngine::GetInstance()->WriteDouble(650, 50, -cameraPos.YValue + m_mouseY, MyDrawEngine::RED);
}