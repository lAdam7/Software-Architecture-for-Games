#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
public:
	void Initialise(Vector2D startingPosition);
	void Update(double frameTime);
};
