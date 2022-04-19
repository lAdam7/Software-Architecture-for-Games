#include "gamecode.h"
#include "myinputs.h"

#include "Wall.h"

IShape2D& Wall::GetShape()
{
	m_collisionShape.PlaceAt(Vector2D(0, 0), Vector2D(250, 250));
	return m_collisionShape;
}

void Wall::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	position = startingPosition;
	angle = 0;
	scale = 4;

	pSoundFX = pSound;

	LoadImg(L"crate1.bmp");

	collidable = true;
	m_activity = Activity::ACTIVE;
};

void Wall::HandleCollision(GameObject& other)
{
	
}

void Wall::HandleMessage(Message& msg)
{

}

void Wall::Update(double frameTime)
{
	m_collisionShape.PlaceAt(Vector2D(30, 0), Vector2D(280, 250));
	MyDrawEngine* engine = MyDrawEngine::GetInstance();
	engine->FillRect(m_collisionShape , MyDrawEngine::RED, 0.0f);
};