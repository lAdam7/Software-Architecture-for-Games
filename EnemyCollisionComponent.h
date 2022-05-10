#pragma once
#include "CollisionComponent.h"

/*
* Inherits from the CollisionComponent for
* collision detection 
*
* @author W19023403
*/
class EnemyCollisionComponent : public CollisionComponent
{
public:
	// Constructor how long the explosion should last
	EnemyCollisionComponent(Circle2D circle, float radius);

	// Bullet hit explosive
	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
}; 
