#include "ShieldCollisionComponent.h"

ShieldCollisionComponent::ShieldCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
}

void ShieldCollisionComponent::Damage(float amount)
{
	m_health -= amount;
};

void ShieldCollisionComponent::Update(GameObject* pObject, float frameTime)
{
	if (m_health < 0)
	{
		pObject->DeleteObject();
	}
};