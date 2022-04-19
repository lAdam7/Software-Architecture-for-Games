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
	m_timer = .1;
	
	m_pSoundFX = pSound;

	m_currentImage = 0;

	CanCollide(false);
	Activate();
};

void Explosion::Update(double frameTime)
{
	m_timer = m_timer - frameTime;

	if (m_currentImage < EXPLOSIONIMAGES)
	{
		LoadImg(m_images[m_currentImage]);
	}

	if (m_timer < 0)
	{
		m_timer = .1;
		m_pSoundFX->PlayExplosion();
		m_currentImage = m_currentImage + 1;
		if (m_currentImage == EXPLOSIONIMAGES-1)
		{
			DeleteObject();
		}
	}
};