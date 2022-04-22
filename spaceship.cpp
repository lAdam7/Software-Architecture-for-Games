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
	Gun::SetClipSize(12);
	Gun::SetReloadTime(3.0f);

	GameObject::SetPosition(startingPosition);
	GameObject::SetAngle(0);
	GameObject::SetScale(0.4f);
	m_shootDelay = 0.05;


	m_timer = .1;
	m_currentImage = 0;

	m_pSoundFX = pSound;

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
		m_pSoundFX->StopEngineSound();
		
		Message msg;
		msg.type = EventType::CHARACTER_DIED;
		msg.location = Vector2D(0, 0);
		msg.pSource = this;
		Game::instance.GetObjectManager().TransmitMessage(msg);
		
		GameObject::DeleteObject();
	}
	else if (typeid(other) == typeid(Wall))
	{
		Wall wall = dynamic_cast<Wall&>(other);
		Vector2D edgeTouching = wall.GetEdge(this);

		if (edgeTouching.XValue == -1)
			//position.XValue = other.GetPosition().XValue - 138;
			m_moveRight = true;
		if (edgeTouching.XValue == 1)
			//position.XValue = other.GetPosition().XValue + 138;
			m_moveLeft = true;
		if (edgeTouching.YValue == -1)
			//position.YValue = other.GetPosition().YValue - 138;
			m_moveTop = true;
		if (edgeTouching.YValue == 1)
			m_moveBottom = true;
			//position.YValue = other.GetPosition().YValue + 138;

			
		
	}
}

void Spaceship::HandleMessage(Message& msg)
{

}

void Spaceship::Update(double frameTime)
{
	Gun::Update((float) frameTime);
	m_timer = m_timer - frameTime;

	if (m_currentImage < IDLEIMAGES)
	{
		GameObject::LoadImg(m_idleImages[m_currentImage]);
	}

	if (m_timer < 0)
	{
		m_timer = .1;
		m_currentImage = m_currentImage + 1;
		if (m_currentImage == IDLEIMAGES - 1)
		{
			m_currentImage = 0;
		}
	}





	MyDrawEngine* test = MyDrawEngine::GetInstance();
	test->theCamera.PlaceAt(GameObject::GetPosition());

	m_shootDelay = m_shootDelay - frameTime;

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	bool joystickAvailable = pInputs->JoystickIsAvailable();
	if (joystickAvailable)
		pInputs->SampleJoystick();

	const float positionAmount = 4.0f;
	const float rotationAmount = 5.0f;
	
	if (pInputs->KeyPressed(DIK_LEFT))
	{
		GameObject::SetAngle(GameObject::GetAngle() - rotationAmount * frameTime);
	}
	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		GameObject::SetAngle(GameObject::GetAngle() + rotationAmount * frameTime);
	}
	
	if ( pInputs->KeyPressed(DIK_W) && !m_moveTop )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(0, positionAmount) + m_velocity * frameTime);
	}
	if ( pInputs->KeyPressed(DIK_S) && !m_moveBottom )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(0, -positionAmount) + m_velocity * frameTime);
	}
	if ( pInputs->KeyPressed(DIK_A) && !m_moveLeft )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(-positionAmount, 0) + m_velocity * frameTime);
	}
	if ( pInputs->KeyPressed(DIK_D) && !m_moveRight )
	{
		GameObject::SetPosition(GameObject::GetPosition() + Vector2D(positionAmount, 0) + m_velocity * frameTime);
	}
	if (pInputs->KeyPressed(DIK_SPACE))
	{
		Gun::Fire(GameObject::GetPosition(), GameObject::GetAngle(), m_pSoundFX);
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

	m_moveRight = false;
	m_moveLeft = false;
	m_moveTop = false;
	m_moveBottom = false;
};