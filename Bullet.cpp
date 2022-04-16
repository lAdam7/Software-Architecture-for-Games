#include "bullet.h";
#include "myinputs.h"
#include "Asteroid.h"
#include <typeinfo>

IShape2D& Bullet::GetShape()
{
	m_collisionShape.PlaceAt(position, 32);
	return m_collisionShape;
}

void Bullet::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Asteroid))
	{
		DeleteObject();
	}
}

void Bullet::Initialise(Vector2D startingPosition, Vector2D vel)
{
	velocity = vel;
	position = startingPosition;
	angle = 0;
	timer = 2;

	MySoundEngine* pSE = MySoundEngine::GetInstance();

	LoadImg(L"bullet.bmp");

	m_activity = ACTIVE;
};

void Bullet::Update(double frameTime)
{
	position = position + velocity;

	timer = timer - frameTime;

	if (timer < 0)
	{
		DeleteObject();
	}
};