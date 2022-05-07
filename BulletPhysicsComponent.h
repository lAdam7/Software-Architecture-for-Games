#pragma once
#include "PhysicsComponent.h"
#include "GameObject.h"

class BulletPhysicsComponent : public PhysicsComponent
{
public:
	Vector2D velocity;
	double m_timer = 2;
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);
};