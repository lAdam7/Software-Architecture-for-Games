#include "gamecode.h"
#include "myinputs.h"

#include "spaceship.h"
#include "Asteroid.h"

IShape2D& Spaceship::GetShape()
{
	m_collisionShape.PlaceAt(position, 32);
	return m_collisionShape;
}

void Spaceship::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	position = startingPosition;
	angle = 0;
	shootDelay = 0.05;

	pSoundFX = pSound;

	LoadImg(L"ship.bmp");

	collidable = true;
	m_activity = ACTIVE;
};

void Spaceship::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Asteroid))
	{
		pSoundFX->StopEngineSound();
		DeleteObject();
	}
}

void Spaceship::Update(double frameTime)
{
	MyDrawEngine* test = MyDrawEngine::GetInstance();
	test->theCamera.PlaceAt(position);

	shootDelay = shootDelay - frameTime;

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	const float positionAmount = 4.0f;
	const float rotationAmount = 0.05f;
		
	if (pInputs->KeyPressed(DIK_LEFT))
	{
		angle = angle - rotationAmount;
	}
	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		angle = angle + rotationAmount;
	}
	if (pInputs->KeyPressed(DIK_W))
	{
		velocity.setBearing(angle, positionAmount);
		position = position + velocity;
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		velocity.setBearing(angle, -positionAmount);
		position = position + velocity;
	}
	if (pInputs->KeyPressed(DIK_SPACE))
	{

		if (shootDelay < 0)
		{
			shootDelay = 0.5;

			GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity;
			velocity.setBearing(angle, 10.0f);
			pBullet->Initialise(position, velocity, pSoundFX);
		}
		
	}
	if (pInputs->KeyPressed(DIK_W) || pInputs->KeyPressed(DIK_S))
	{
		pSoundFX->StartEngineSound();
	}
	else
	{
		pSoundFX->StopEngineSound();
	}
};