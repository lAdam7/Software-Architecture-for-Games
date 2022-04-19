#include "Mouse.h"
#include "myinputs.h"
#include "mydrawengine.h"

void Mouse::StartUp()
{
	Rectangle2D test = MyDrawEngine::GetInstance()->GetViewport();
	widthRadius = test.GetTopRight().XValue;
}

void Mouse::UpdateMouse()
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleMouse();
	pInputs->SampleJoystick();

	float xAxis;
	if (pInputs->JoystickIsAvailable())
	{
		xAxis = pInputs->GetJoystickX()*0.06;
	}
	else
	{
		xAxis = pInputs->GetMouseDX();
	}
	float yAxis;
	if (pInputs->JoystickIsAvailable())
	{
		yAxis = pInputs->GetJoystickY()*0.06;
	}
	else
	{
		yAxis = pInputs->GetMouseDY();
	}


	if (xAxis - tolerance > 0 && mouseX < (widthRadius - 50))
	{
		mouseX = mouseX + (xAxis * sensitivity);
		if (mouseX > (widthRadius - 50))
			mouseX = widthRadius - 50;
	}
	else if (xAxis + tolerance < 0 && mouseX > (-widthRadius + 50))
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
		mouseY = mouseY - (yAxis *sensitivity);
		if (mouseY < -950)
			mouseY = -950;
	}
	
	Vector2D cameraPos = MyDrawEngine::GetInstance()->theCamera.GetCameraPosition();

	//MyDrawEngine::GetInstance()->FillCircle(Vector2D( cameraPos.XValue + mouseX, -cameraPos.YValue + mouseY), 7.0f, MyDrawEngine::YELLOW);

	//MyDrawEngine::GetInstance()->WriteInt(100, 50, mouseX, MyDrawEngine::GREEN);
	//MyDrawEngine::GetInstance()->WriteInt(150, 50, mouseY, MyDrawEngine::GREEN);


	//MyDrawEngine::GetInstance()->WriteInt(250, 50, pInputs->GetJoystickX(), MyDrawEngine::GREEN);
	
	//MyDrawEngine::GetInstance()->WriteInt(250, 50, test.GetBottomLeft().XValue, MyDrawEngine::GREEN);
}