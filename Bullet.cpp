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
	m_velocity = vel;
	SetPosition(startingPosition + m_velocity);
	SetAngle(0);
	m_timer = 2;
	pSound->PlayShot();

	LoadImg(L"bullet.bmp");

	CanCollide(true);
	Activate();
};

void Bullet::Update(double frameTime)
{
	SetPosition(GetPosition() + m_velocity);

	m_timer = m_timer - frameTime;

	if (m_timer < 0)
	{
		DeleteObject();
	}
};