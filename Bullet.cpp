#include "bullet.h";
#include "myinputs.h"

void Bullet::Initialise(Vector2D startingPosition)
{
	position = startingPosition;
	angle = 0;

	MySoundEngine* pSE = MySoundEngine::GetInstance();

	LoadImg(L"bullet.bmp");

	active = true;
};

void Bullet::Update(double frameTime)
{
	
};