#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float timer;
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity);
	void Update(double frameTime);
};
