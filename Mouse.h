#pragma once
#include "GameObject.h"

class Mouse : public GameObject
{
private:
	Circle2D m_collisionShape;

	float sensitivity = 4.0f;
	float mouseX = 0.0f;
	float mouseY = 0.0f;
	float tolerance = 0.3f;
	float widthRadius;
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
	void Update(double frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void HandleMessage(Message& msg);
};

/*
class Mouse
{
private:
	float sensitivity = 4.0f;
	float mouseX = 0.0f;
	float mouseY = 0.0f;
	float tolerance = 0.3f;
	float widthRadius;
public:
	void StartUp();
	void UpdateMouse();
};
*/