#include "gamecode.h"
#include "myinputs.h"

#include "Wall.h"

IShape2D& Wall::GetShape()
{
	m_collisionShape.PlaceAt(GetPosition() + Vector2D(-128, -128), GetPosition() + Vector2D(128, 128));
	return m_collisionShape;
}

void Wall::Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSound)
{
	SetPosition(startingPosition);
	//SetAngle(0);

	m_pSoundFX = pSound;

	//LoadImg(filename);

	//CanCollide(true);
	Activate();
};

void Wall::SetImageQuick(const wchar_t* filename)
{
	LoadImg(filename);
}

void Wall::HandleCollision(GameObject& other)
{
	
}

void Wall::HandleMessage(Message& msg)
{

}

void Wall::Update(double frameTime)
{
	//m_collisionShape.PlaceAt(Vector2D(30, 0), Vector2D(280, 250));
	//MyDrawEngine* engine = MyDrawEngine::GetInstance();
	//engine->FillRect(m_collisionShape , MyDrawEngine::RED, 0.0f);
}

Vector2D Wall::GetEdge(GameObject* other)
{
	Vector2D edges = Vector2D(0, 0);

	if (other->GetPosition().XValue < GetPosition().XValue)
		edges.XValue--;
	if (other->GetPosition().XValue > GetPosition().XValue)
		edges.XValue++;
	if (other->GetPosition().YValue > GetPosition().YValue)
		edges.YValue++;
	if (other->GetPosition().YValue < GetPosition().YValue)
		edges.YValue--;

	return edges;
}