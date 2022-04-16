#include "spaceship.h";
#include "myinputs.h"

void Spaceship::Initialise(Vector2D startingPosition)
{
	position = startingPosition;
	angle = 0;

	MySoundEngine* pSE = MySoundEngine::GetInstance();
	shootSound = pSE->LoadWav(L"shoot.wav");
	thrustSound = pSE->LoadWav(L"thrustloop2.wav");

	LoadImg(L"ship.bmp");

	active = true;
};

void Spaceship::Update(double frameTime)
{
	//POINT p;
	//GetCursorPos(&p);
	//ScreenToClient(GetForegroundWindow(), &p);
	
		//cursor position now in p.x and p.y
	//position = Vector2D(p.x, p.y);
	
	
	//	position = Vector2D(GetCursorPos(&p).x, 500);
	
	//velocity.setBearing(angle, 4.0f);
	//position = position + velocity;


/*
	const float positionAmount = 4.0f;
	const float rotationAmount = 0.05f;

	if (pInputs->KeyPressed(DIK_LEFT))
	{
		angle = angle - rotationAmount;
	}
	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		angle = angle + rotationAmount;
	}
	if (pInputs->KeyPressed(DIK_W))
	{
		//velocity.setBearing(angle, positionAmount);
		//Vector2D friction = -0.5 * velocity;
		//velocity = velocity + friction * frameTime;

		//Vector2D acceleration(0, 30);
		//velocity = velocity + acceleration * frameTime;
		velocity.setBearing(angle, positionAmount);
		position = position + velocity;
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		//Vector2D acceleration(0, -30);
		//velocity = velocity + acceleration;
		velocity.setBearing(angle, -positionAmount);
		position = position + velocity;
	}
	if (pInputs->NewKeyPressed(DIK_SPACE))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(shootSound);
	}
	if (pInputs->KeyPressed(DIK_W) || pInputs->KeyPressed(DIK_S))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(thrustSound, true);
	}
	else
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(thrustSound, false);
		pSE->Stop(thrustSound);
	}
	//position = position + velocity * frameTime;*/
};