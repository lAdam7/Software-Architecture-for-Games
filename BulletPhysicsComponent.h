#pragma once
#include "PhysicsComponent.h"
#include "GameObject.h"

/*
* Inherits from the PhysicsComponent, for
* updating the velocity and moving the bullet
* in the right direction
*
* @author W19023403
*/
class BulletPhysicsComponent : public PhysicsComponent
{
private:
	// The direction the bullet is firing towards
	Vector2D m_velocity;
public:
	// Update position of bullet with the velocity
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);

	// Set the velocity
	void SetVelocity(Vector2D velocity);
	// Get the velocity
	Vector2D GetVelocity();
};