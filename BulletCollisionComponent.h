#pragma once
#include "CollisionComponent.h"

/*
* Inherits from the CollisionComponent for
* collision detection
*
* @author W19023403
*/
class BulletCollisionComponent : public CollisionComponent
{
public:
	// Constructor how long the explosion should last
	BulletCollisionComponent(Circle2D circle, float radius);

	// Bullet hit explosive
	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
};
