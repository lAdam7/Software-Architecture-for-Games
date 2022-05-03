#pragma once
#include "GameObject.h"

class PlayerLegs : public GameObject
{
private:
	Circle2D m_collisionShape;
	SoundFX* m_pSoundFX;
	static const int IDLEIMAGES = 20;
	const wchar_t* m_idleImages[IDLEIMAGES] = { L"survivorRun_0.png", L"survivorRun_1.png" , L"survivorRun_2.png", L"survivorRun_3.png", L"survivorRun_4.png", L"survivorRun_5.png", L"survivorRun_6.png", L"survivorRun_7.png", L"survivorRun_8.png", L"survivorRun_9.png", L"survivorRun_10.png", L"survivorRun_11.png", L"survivorRun_12.png", L"survivorRun_13.png", L"survivorRun_14.png", L"survivorRun_15.png", L"survivorRun_16.png", L"survivorRun_17.png", L"survivorRun_18.png", L"survivorRun_19.png" };
	
	int m_currentImage;
	double m_timer;

	GameObject* m_mainCharacter;
public:
	void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
	void Update(double frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void HandleMessage(Message& msg);
};
