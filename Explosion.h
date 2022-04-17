#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
private:
	Circle2D m_collisionShape;
	static const int EXPLOSIONIMAGES = 8;
	const wchar_t* images[EXPLOSIONIMAGES] = { L"explosion1.bmp", L"explosion2.bmp", L"explosion3.bmp", L"explosion4.bmp", L"explosion5.bmp", L"explosion6.bmp", L"explosion7.bmp", L"explosion8.bmp" };
	int currentImage;
	float timer;
	SoundFX* pSoundFX;
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
	void Update(double frameTime);

	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};