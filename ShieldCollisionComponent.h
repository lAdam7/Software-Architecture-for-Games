#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

class ShieldCollisionComponent : public CollisionComponent
{
public:
	float m_health;
	ShieldCollisionComponent(Circle2D circle, float radius);
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
	void Damage(float amount);
};