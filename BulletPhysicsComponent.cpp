#include "BulletPhysicsComponent.h"

/*
* Inherits from the PhysicsComponent, for
* updating the velocity and moving the bullet
* in the right direction
*
* @author W19023403
*/

// Update position of bullet with the velocity
void BulletPhysicsComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	pObject->SetPosition(pObject->GetPosition() + m_velocity * frameTime);
};

// Set the velocity
void BulletPhysicsComponent::SetVelocity(Vector2D velocity)
{
	m_velocity = velocity;
};
// Get the velocity
Vector2D BulletPhysicsComponent::GetVelocity()
{
	return m_velocity;
};