#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

// Different drops available
enum class Type_Drop { SHOTGUN, BOUNCING_BULLET, FORCEFIELD };

/*
* Inherits from the CollisionComponent to handle collisions
* 
* @author W19023403
*/
class DropCollisionComponent : public CollisionComponent
{
private:
	// The type of drop 
	Type_Drop m_dropType;
public:
	// Constructor set the CollisionComponent and set the type of drop
	DropCollisionComponent(Circle2D circle, float radius, Type_Drop drop);

	// Call when object collides with another collidable object
	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
};