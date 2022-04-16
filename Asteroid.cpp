#include "Asteroid.h";
#include "myinputs.h"
#include "Bullet.h"

IShape2D& Asteroid::GetShape()
{
	m_collisionShape.PlaceAt(position, 70);
	return m_collisionShape;
}

void Asteroid::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		DeleteObject();
	}
}

void Asteroid::Initialise(Vector2D startingPosition, Vector2D velocity)
{
	position = startingPosition;
	angle = 0;

	const wchar_t* images[4] = { L"rock1.bmp", L"rock2.bmp", L"rock3.bmp", L"rock4.bmp"};

	LoadImg(images[rand()%4]);
	
	m_activity = ACTIVE;
};

void Asteroid::Update(double frameTime)
{

};