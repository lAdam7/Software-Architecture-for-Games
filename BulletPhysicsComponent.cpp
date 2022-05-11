#include "BulletPhysicsComponent.h"

void BulletPhysicsComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	pObject->SetPosition(pObject->GetPosition() + m_velocity * frameTime);
};

void BulletPhysicsComponent::SetVelocity(Vector2D velocity)
{
	m_velocity = velocity;
};
Vector2D BulletPhysicsComponent::GetVelocity()
{
	return m_velocity;
};