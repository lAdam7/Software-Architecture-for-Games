#pragma once
#include "CollisionComponent.h"

/*
* Inherits from the CollisionComponent for
* collision detection
*
* @author W19023403
*/
class RecurringCollisionComponent : public CollisionComponent
{
public:
	// Constructor how long the explosion should last
	RecurringCollisionComponent(Rectangle2D rectangle, float x, float y);

	// Bullet hit explosive
	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
};
