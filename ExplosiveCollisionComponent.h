#pragma once
#include "CollisionComponent.h"

/*
* Inherits from the CollisionComponent for
* collision detection of a bullet hitting the
* explosive
*
* @author W19023403
*/
class ExplosiveCollisionComponent : public CollisionComponent
{
public:
	// Constructor how long the explosion should last
	ExplosiveCollisionComponent(Circle2D circle, float radius);

	// Bullet hit explosive
	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
};