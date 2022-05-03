#include "gamecode.h"
#include "myinputs.h"

#include "PlayerLegs.h"

IShape2D& PlayerLegs::GetShape()
{
	m_collisionShape.PlaceAt(GetPosition(), 32);
	return m_collisionShape;
}

void PlayerLegs::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	SetPosition(startingPosition);
	SetAngle(0);
	SetScale(0.25f);

	m_timer = .1;
	m_currentImage = 0;

	m_pSoundFX = pSound;

	LoadImg(L"idle_0.png");

	ReceiveMessages(true);
	CanCollide(false);
	Activate();

	//m_mainCharacter = Game::instance.GetObjectManager().Create(L"Spaceship");
	//m_mainCharacter->Initialise(GetPosition(), Vector2D(0, 0), m_pSoundFX);
};

void PlayerLegs::HandleCollision(GameObject& other)
{
	
}

void PlayerLegs::HandleMessage(Message& msg)
{
	if (msg.type == EventType::CHARACTER_DIED) // shapeship destroyed
	{
		DeleteObject();
	}
}

void PlayerLegs::Update(double frameTime)
{
	SetPosition(m_mainCharacter->GetPosition());
	SetAngle(m_mainCharacter->GetAngle());

	m_timer = m_timer - frameTime;

	if (m_currentImage < IDLEIMAGES)
	{
		LoadImg(m_idleImages[m_currentImage]);
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
};