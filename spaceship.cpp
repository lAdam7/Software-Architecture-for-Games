#include "gamecode.h"
#include "myinputs.h"

#include "spaceship.h"
#include "Asteroid.h"
#include "Wall.h"

IShape2D& Spaceship::GetShape()
{
	Vector2D offset;
	offset.setBearing(angle, -45.0f);

	m_collisionShape.PlaceAt(position + offset, 40);
	return m_collisionShape;
}

void Spaceship::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	position = startingPosition;
	angle = 0.0f;
	shootDelay = 0.05;

	scale = 0.4f;

	timer = .1;
	currentImage = 0;

	pSoundFX = pSound;

	LoadImg(L"ship.bmp");

	//GameObject* pFeet = Game::instance.GetObjectManager().Create(L"Feet");
	//pFeet->Initialise(position, Vector2D(0, 0), pSoundFX);

	collidable = true;
	m_activity = Activity::ACTIVE;
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
		
		DeleteObject();
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
	timer = timer - frameTime;

	if (currentImage < IDLEIMAGES)
	{
		LoadImg(idleImages[currentImage]);
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
	test->theCamera.PlaceAt(position);

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
		angle = angle - rotationAmount;
	}
	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		angle = angle + rotationAmount;
	}
	MyDrawEngine* testEngine = MyDrawEngine::GetInstance();
	testEngine->WriteInt(300, 50, 5, MyDrawEngine::CYAN);
	if ( (pInputs->KeyPressed(DIK_W)) )
	{
		//velocity.setBearing(angle, positionAmount);
		position = position + Vector2D(0, 3.0f) + velocity;
	}
	if ( (pInputs->KeyPressed(DIK_S)) )
	{
		//velocity.setBearing(angle, -positionAmount);
		//position = position + velocity;

		position = position + Vector2D(0, -3.0f) + velocity;
	}
	if ( (pInputs->KeyPressed(DIK_A)) )
	{
		position = position + Vector2D(-3.0f, 0) + velocity;
	}
	if ( (pInputs->KeyPressed(DIK_D)) )
	{
		position = position + Vector2D(3.0f, 0) + velocity;
	}
	if (pInputs->KeyPressed(DIK_SPACE))
	{

		if (shootDelay < 0)
		{
			shootDelay = 0.05;

			GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity;
			velocity.setBearing(angle, 10.0f); //10.0 before

			Vector2D startingAngle;
			startingAngle.setBearing(angle + 0.55f, 50.0f);

			pBullet->Initialise(position + startingAngle, velocity, pSoundFX);
		}
		
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