#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

enum class Type_Drop { SHOTGUN, BOUNCING_BULLET, FORCEFIELD };
class DropCollisionComponent : public CollisionComponent
{
private:
	Type_Drop m_dropType;
public:
	DropCollisionComponent(Circle2D circle, float radius, Type_Drop drop);
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
};