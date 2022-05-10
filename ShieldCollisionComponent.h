#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

class ShieldCollisionComponent : public CollisionComponent
{
private:
public:
	ShieldCollisionComponent(Circle2D circle, float radius);
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
};