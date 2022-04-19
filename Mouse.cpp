#include "Mouse.h"
#include "myinputs.h"
#include "mydrawengine.h"

void Mouse::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	Rectangle2D test = MyDrawEngine::GetInstance()->GetViewport();
	widthRadius = test.GetTopRight().XValue;

	LoadImg(L"ship.bmp");

	GameObject::Activate();

};

void Mouse::Update(double frameTime)
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleMouse();

	int xAxis = pInputs->GetMouseDX();
	int yAxis = pInputs->GetMouseDY();

	if (xAxis - tolerance > 0 && mouseX < (widthRadius - 50))
	{
		mouseX = mouseX + (xAxis * sensitivity);
		if (mouseX > (widthRadius - 50))
			mouseX = widthRadius - 50;
	}
	else if (xAxis + tolerance < 0 && mouseX >(-widthRadius + 50))
	{
		mouseX = mouseX - (-xAxis * sensitivity);
		if (mouseX < (-widthRadius + 50))
			mouseX = -widthRadius + 50;
	}

	if (yAxis + tolerance < 0 && mouseY < 950)
	{
		mouseY = mouseY + (-yAxis * sensitivity);
		if (mouseY > 950)
			mouseY = 950;
	}
	else if (yAxis - tolerance > 0 && mouseY > -950)
	{
		mouseY = mouseY - (yAxis * sensitivity);
		if (mouseY < -950)
			mouseY = -950;
	}

	Vector2D cameraPos = MyDrawEngine::GetInstance()->theCamera.GetCameraPosition();

	SetPosition(Vector2D(cameraPos.XValue + mouseX, -cameraPos.YValue + mouseY));
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