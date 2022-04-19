#include "bullet.h"
#include "Asteroid.h"

IShape2D& Bullet::GetShape()
{
	m_collisionShape.PlaceAt(GetPosition(), 32);
	return m_collisionShape;
}

void Bullet::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Asteroid))
	{
		DeleteObject();
	}
}

void Bullet::HandleMessage(Message& msg)
{

}

void Bullet::Initialise(Vector2D startingPosition, Vector2D vel, SoundFX* pSound)
{
	velocity = vel;
	SetPosition(startingPosition + velocity);
	SetAngle(0);
	timer = 2;
	pSound->PlayShot();

	LoadImg(L"bullet.bmp");

	CanCollide(true);
	Activate();
};

void Bullet::Update(double frameTime)
{
	SetPosition(GetPosition() + velocity);

	timer = timer - frameTime;

	if (timer < 0)
	{
		DeleteObject();
	}
};