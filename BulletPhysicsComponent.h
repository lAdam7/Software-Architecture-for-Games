#pragma once
#include "PhysicsComponent.h"
#include "GameObject.h"

class BulletPhysicsComponent : public PhysicsComponent
{
private:
	Vector2D m_velocity;
public:
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);

	void SetVelocity(Vector2D velocity);
	Vector2D GetVelocity();
};