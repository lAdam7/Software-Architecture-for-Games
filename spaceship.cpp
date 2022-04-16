#include "spaceship.h";
#include "myinputs.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "gamecode.h"
#include <typeinfo>
#include "Asteroid.h"

IShape2D& Spaceship::GetShape()
{
	m_collisionShape.PlaceAt(position, 32);
	return m_collisionShape;
}

void Spaceship::Initialise(Vector2D startingPosition, Vector2D velocity)
{
	position = startingPosition;
	angle = 0;
	shootDelay = 0.05;

	MySoundEngine* pSE = MySoundEngine::GetInstance();
	shootSound = pSE->LoadWav(L"shoot.wav");
	thrustSound = pSE->LoadWav(L"thrustloop2.wav");

	LoadImg(L"ship.bmp");

	collidable = true;
	m_activity = ACTIVE;
};

void Spaceship::HandleCollision(GameObject& other)
{
	if (typeid(other) == typeid(Asteroid))
	{
		DeleteObject();
	}
}

void Spaceship::Update(double frameTime)
{
	shootDelay = shootDelay - frameTime;
	//POINT p;
	//GetCursorPos(&p);
	//ScreenToClient(GetForegroundWindow(), &p);
	
		//cursor position now in p.x and p.y
	//position = Vector2D(p.x, p.y);
	
	
	//	position = Vector2D(GetCursorPos(&p).x, 500);
	
	//velocity.setBearing(angle, 4.0f);
	//position = position + velocity;

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
		//velocity.setBearing(angle, positionAmount);
		//Vector2D friction = -0.5 * velocity;
		//velocity = velocity + friction * frameTime;

		//Vector2D acceleration(0, 30);
		//velocity = velocity + acceleration * frameTime;
		velocity.setBearing(angle, positionAmount);
		position = position + velocity;
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		//Vector2D acceleration(0, -30);
		//velocity = velocity + acceleration;
		velocity.setBearing(angle, -positionAmount);
		position = position + velocity;
	}
	if (pInputs->KeyPressed(DIK_SPACE))
	{

		if (shootDelay < 0)
		{
			shootDelay = 0.5;

			//Bullet* pBullet = new Bullet();
			GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity;
			velocity.setBearing(angle, 10.0f);
			pBullet->Initialise(position, velocity);
			//Game::instance.GetObjectManager().AddObject(pBullet);

			MySoundEngine* pSE = MySoundEngine::GetInstance();
			pSE->Play(shootSound);
		}
		
	}
	if (pInputs->KeyPressed(DIK_W) || pInputs->KeyPressed(DIK_S))
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(thrustSound, true);
	}
	else
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		pSE->Play(thrustSound, false);
		pSE->Stop(thrustSound);
	}
	//position = position + velocity * frameTime;
};