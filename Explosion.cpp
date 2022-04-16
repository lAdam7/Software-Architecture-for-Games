#include "Explosion.h"
#include "myinputs.h"

IShape2D& Explosion::GetShape()
{
	m_collisionShape.PlaceAt(position, 1);
	return m_collisionShape;
}

void Explosion::HandleCollision(GameObject& other)
{
	
}

void Explosion::Initialise(Vector2D startingPosition, Vector2D velocity)
{
	position = startingPosition;
	timer = .1;
	//angle = 0;
	
	//const wchar_t* images[4] = { L"rock1.bmp", L"rock2.bmp", L"rock3.bmp", L"rock4.bmp" };

	//LoadImg(images[rand() % 4]);
	currentImage = 0;

	collidable = false;
	m_activity = ACTIVE;
};

void Explosion::Update(double frameTime)
{
	timer = timer - frameTime;

	if (currentImage < 8)
	{
		LoadImg(images[currentImage]);
	}

	if (timer < 0)
	{
		timer = .1;

		currentImage = currentImage + 1;
		if (currentImage == 7)
		{
			m_activity = CAN_DELETE;
		}
	}
};