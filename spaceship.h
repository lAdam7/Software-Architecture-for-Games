#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Spaceship: public GameObject
{
	private:
		Vector2D velocity;
		SoundIndex shootSound;
		SoundIndex thrustSound;
		double shootDelay;
	public:
		void Initialise(Vector2D startingPosition, Vector2D velocity);
		void Update(double frameTime);
};
