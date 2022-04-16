#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Circle2D m_collisionShape;
	Vector2D velocity;
	float timer;
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
	void Update(double frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};
