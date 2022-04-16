#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Asteroid : public GameObject
{
private:
	
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity);
	void Update(double frameTime);
};