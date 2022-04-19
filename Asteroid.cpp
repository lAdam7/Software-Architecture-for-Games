#include "gamecode.h"
#include "myinputs.h"

#include "Asteroid.h"
#include "Bullet.h"

IShape2D& Asteroid::GetShape()
{
	m_collisionShape.PlaceAt(GetPosition(), 70);
	return m_collisionShape;
}

void Asteroid::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Bullet))
	{
		GameObject* pExplosion = Game::instance.GetObjectManager().Create(L"Explosion");
		pExplosion->Initialise(GetPosition(), Vector2D(0, 0), pSoundFX);
		DeleteObject();
	}
}

void Asteroid::HandleMessage(Message& msg)
{
	if (msg.type == EventType::OBJECT_DESTROYED) // shapeship destroyed
	{
		GameObject* pExplosion = Game::instance.GetObjectManager().Create(L"Explosion");
		pExplosion->Initialise(GetPosition(), Vector2D(0, 0), pSoundFX);
		DeleteObject();
	}
}

void Asteroid::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	SetPosition(startingPosition);
	SetAngle(0);

	pSoundFX = pSound;

	const wchar_t* images[4] = { L"rock1.bmp", L"rock2.bmp", L"rock3.bmp", L"rock4.bmp"};

	LoadImg(images[rand()%4]);
	
	ReceiveMessages(true);
	CanCollide(true);
	Activate();
};

void Asteroid::Update(double frameTime)
{
};