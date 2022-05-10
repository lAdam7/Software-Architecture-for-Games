#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

/*
* Inherits from the CollisionComponent, 
* removes the shield once collided enough
* with the object, lost health
*
* @author W19023403
*/
class ShieldCollisionComponent : public CollisionComponent
{
public:
	// Constructor use base class collision
	ShieldCollisionComponent(Circle2D circle, float radius);
	// Check if object has lost all health, if so remove
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
};