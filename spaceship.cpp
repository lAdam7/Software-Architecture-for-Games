#include "gamecode.h"
#include "myinputs.h"

#include "spaceship.h"
#include "Asteroid.h"
#include "Wall.h"

IShape2D& Spaceship::GetShape()
{
	Vector2D offset;
	offset.setBearing(GameObject::GetAngle(), -45.0f);

	m_collisionShape.PlaceAt(GameObject::GetPosition() + offset, 40);
	return m_collisionShape;
}

void Spaceship::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	Gun::SetBulletDelay(0.1f);
	Gun::SetClipSize(100);
	Gun::SetReloadTime(8.0f);

	GameObject::SetPosition(startingPosition);
	GameObject::SetAngle(0);
	GameObject::SetScale(0.4f);
	shootDelay = 0.05;


	timer = .1;
	currentImage = 0;

	pSoundFX = pSound;

	GameObject::LoadImg(L"ship.bmp");

	//GameObject* pFeet = Game::instance.GetObjectManager().Create(L"Feet");
	//pFeet->Initialise(position, Vector2D(0, 0), pSoundFX);

	GameObject::CanCollide(true);
	GameObject::Activate();
};

void Spaceship::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Asteroid))
	{
		pSoundFX->StopEngineSound();
		
		Message msg;
		msg.type = EventType::OBJECT_DESTROYED;
		msg.location = Vector2D(0, 0);
		msg.pSource = this;

		Game::instance.GetObjectManager().TransmitMessage(msg);
		
		GameObject::DeleteObject();
	}
	else if (typeid(other) == typeid(Wall))
	{

	}
}

void Spaceship::HandleMessage(Message& msg)
{

}

void Spaceship::Update(double frameTime)
{
	Gun::Update(frameTime);
	timer = timer - frameTime;

	if (currentImage < IDLEIMAGES)
	{
		GameObject::LoadImg(idleImages[currentImage]);
	}

	if (timer < 0)
	{
		timer = .1;
		currentImage = currentImage + 1;
		if (currentImage == IDLEIMAGES - 1)
		{
			currentImage = 0;
		}
	}





	MyDrawEngine* test = MyDrawEngine::GetInstance();
	test->theCamera.PlaceAt(GameObject::GetPosition());

	shootDelay = shootDelay - frameTime;

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	bool joystickAvailable = pInputs->JoystickIsAvailable();
	if (joystickAvailable)
		pInputs->SampleJoystick();

	const float positionAmount = 4.0f;
	const float rotationAmount = 0.03f;
		
	if (pInputs->KeyPressed(DIK_LEFT))
	{
		GameObject::SetAngle(GameObject::GetAngle() - rotationAmount);
	}
	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		GameObject::SetAngle(GameObject::GetAngle() + rotationAmount);
	}
	
	if ( (pInputs->KeyPressed(DIK_W)) )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(0, 3.0f) + velocity);
	}
	if ( (pInputs->KeyPressed(DIK_S)) )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(0, -3.0f) + velocity);
	}
	if ( (pInputs->KeyPressed(DIK_A)) )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(-3.0f, 0) + velocity);
	}
	if ( (pInputs->KeyPressed(DIK_D)) )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(3.0f, 0) + velocity);
	}
	if (pInputs->KeyPressed(DIK_SPACE))
	{
		Gun::Fire(GameObject::GetPosition(), GameObject::GetAngle(), pSoundFX);
		/*
		if (shootDelay < 0)
		{
			shootDelay = 0.05;

			GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity;
			velocity.setBearing(GameObject::GetAngle(), 10.0f); //10.0 before

			Vector2D startingAngle;
			startingAngle.setBearing(GameObject::GetAngle() + 0.55f, 50.0f);

			pBullet->Initialise(GameObject::GetPosition() + startingAngle, velocity, pSoundFX);
		}
		*/
	}
	if (pInputs->KeyPressed(DIK_W) || pInputs->KeyPressed(DIK_S))
	{
		//pSoundFX->StartEngineSound();
	}
	else
	{
		//pSoundFX->StopEngineSound();
	}	
};