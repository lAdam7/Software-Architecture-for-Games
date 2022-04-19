#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Circle2D m_collisionShape;
	Vector2D m_velocity;
	double m_timer;
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
	void Update(double frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void HandleMessage(Message& msg);
};
