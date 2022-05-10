#pragma once
#include "CollisionComponent.h"

/*
* Inherits from the CollisionComponent for
* collision detection for when a player 
* touches the key
*
* @author W19023403
*/
class KeyCollisionComponent : public CollisionComponent
{
public:
	KeyCollisionComponent(Circle2D circle, float radius);

	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
};