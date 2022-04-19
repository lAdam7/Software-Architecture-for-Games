#include "gamecode.h"
#include "myinputs.h"

#include "Feet.h"

IShape2D& Feet::GetShape()
{
	m_collisionShape.PlaceAt(GetPosition(), 32);
	return m_collisionShape;
}

void Feet::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	SetPosition(startingPosition);
	SetAngle(0);
	SetScale(0.25f);

	timer = .1;
	currentImage = 0;

	pSoundFX = pSound;

	LoadImg(L"idle_0.png");

	CanCollide(false);
	Activate();

	mainCharacter = Game::instance.GetObjectManager().Create(L"Spaceship");
	mainCharacter->Initialise(GetPosition(), Vector2D(0, 0), pSoundFX);
};

void Feet::HandleCollision(GameObject& other)
{
	
}

void Feet::HandleMessage(Message& msg)
{

}

void Feet::Update(double frameTime)
{
	SetPosition(mainCharacter->GetPosition());
	SetAngle(mainCharacter->GetAngle());

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
};