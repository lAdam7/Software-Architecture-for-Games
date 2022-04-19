#include "Mouse.h"
#include "myinputs.h"
#include "mydrawengine.h"

void Mouse::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	Rectangle2D test = MyDrawEngine::GetInstance()->GetViewport();
	m_widthRadius = test.GetTopRight().XValue;

	LoadImg(L"ship.bmp");

	GameObject::Activate();

};

void Mouse::Update(double frameTime)
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

	SetPosition(Vector2D(cameraPos.XValue + m_mouseX, -cameraPos.YValue + m_mouseY));
}

IShape2D& Mouse::GetShape()
{
	Vector2D offset;
	offset.setBearing(GameObject::GetAngle(), -45.0f);

	m_collisionShape.PlaceAt(GameObject::GetPosition() + offset, 40);
	return m_collisionShape;
}

void Mouse::HandleCollision(GameObject& other)
{
	
}

void Mouse::HandleMessage(Message& msg)
{

}