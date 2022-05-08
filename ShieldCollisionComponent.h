#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

class ShieldCollisionComponent : public CollisionComponent
{
public:
	float m_health = 100;
	ShieldCollisionComponent(Circle2D circle, float radius);
	void Update(GameObject* pObject, float frameTime);
	void Damage(float amount);
};