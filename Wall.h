#pragma once
#include "GameObject.h"

class Wall : public GameObject
{
private:
	Rectangle2D m_collisionShape;
	SoundFX* m_pSoundFX;
	const float HEIGHT = 150.0f;
	const float WIDTH = 180.0f;
public:
	void SetImageQuick(const wchar_t* filename);
	void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX);
	void Update(double frameTime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
	void HandleMessage(Message& msg);
	Vector2D GetEdge(GameObject* other );
};
