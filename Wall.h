#pragma once
#include "GameObject.h"

class Wall : public GameObject
{
private:
	Rectangle2D m_collisionShape;
	SoundFX* pSoundFX;
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
	void Update(double frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void HandleMessage(Message& msg);
};
