#pragma once
#include "GameObject.h"
#include "Gun.h"

class Spaceship: public GameObject, public Gun
{
	private:
		Vector2D m_velocity;
		double m_shootDelay;
		Circle2D m_collisionShape;
		SoundFX* m_pSoundFX;

		static const int IDLEIMAGES = 20;
		const wchar_t* m_idleImages[IDLEIMAGES] = { L"survivorRifle_0.png", L"survivorRifle_1.png", L"survivorRifle_2.png", L"survivorRifle_3.png", L"survivorRifle_4.png", L"survivorRifle_5.png", L"survivorRifle_6.png", L"survivorRifle_7.png", L"survivorRifle_8.png", L"survivorRifle_9.png", L"survivorRifle_10.png", L"survivorRifle_11.png", L"survivorRifle_12.png", L"survivorRifle_13.png", L"survivorRifle_14.png", L"survivorRifle_15.png", L"survivorRifle_16.png", L"survivorRifle_17.png", L"survivorRifle_18.png", L"survivorRifle_19.png" };
		static const int RUNIMAGES = 8;
		const wchar_t* m_runImages[RUNIMAGES] = { L"run1.png", L"run2.png", L"run3.png", L"run4.png", L"run5.png", L"run6.png", L"run7.png", L"run8.png" };
		static const int SHOOTIMAGES = 3;
		const wchar_t* m_shootImagees[SHOOTIMAGES] = { L"shoot1.png", L"shoot2.png", L"shoot3.png" };
		static const int DEADIMAGES = 10;
		const wchar_t* m_deadImages[DEADIMAGES] = { L"dead1.png", L"dead2.png", L"dead3.png", L"dead4.png", L"dead5.png", L"dead6.png", L"dead7.png", L"dead8.png", L"dead9.png", L"dead10.png" };
	
		int m_currentImage;
		double m_timer;
	public:
		void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
		void Update(double frameTime);
		IShape2D& GetShape();
		void HandleCollision(GameObject& other);
		void HandleMessage(Message& msg);
};
