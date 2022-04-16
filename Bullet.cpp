#include "bullet.h";
#include "myinputs.h"

void Bullet::Initialise(Vector2D startingPosition, Vector2D vel)
{
	velocity = vel;
	position = startingPosition;
	angle = 0;
	timer = 2;

	MySoundEngine* pSE = MySoundEngine::GetInstance();

	LoadImg(L"bullet.bmp");

	active = true;
};

void Bullet::Update(double frameTime)
{
	position = position + velocity;

	timer = timer - frameTime;

	if (timer < 0)
	{
		active = false;
	}
};