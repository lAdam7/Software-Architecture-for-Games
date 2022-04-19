#include "Explosion.h"

IShape2D& Explosion::GetShape()
{
	m_collisionShape.PlaceAt(GetPosition(), 1);
	return m_collisionShape;
}

void Explosion::HandleCollision(GameObject& other)
{
	
}

void Explosion::HandleMessage(Message& msg)
{

}

void Explosion::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	SetPosition(startingPosition);
	timer = .1;
	
	pSoundFX = pSound;

	currentImage = 0;

	CanCollide(false);
	Activate();
};

void Explosion::Update(double frameTime)
{
	timer = timer - frameTime;

	if (currentImage < EXPLOSIONIMAGES)
	{
		LoadImg(images[currentImage]);
	}

	if (timer < 0)
	{
		timer = .1;
		pSoundFX->PlayExplosion();
		currentImage = currentImage + 1;
		if (currentImage == EXPLOSIONIMAGES-1)
		{
			DeleteObject();
		}
	}
};