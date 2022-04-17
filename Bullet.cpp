#include "bullet.h";
#include "Asteroid.h"

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

void Bullet::Initialise(Vector2D startingPosition, Vector2D vel, SoundFX* pSound)
{
	velocity = vel;
	position = startingPosition;
	angle = 0;
	timer = 2;

	pSound->PlayShot();

	LoadImg(L"bullet.bmp");

	collidable = true;
	m_activity = Activity::ACTIVE;
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