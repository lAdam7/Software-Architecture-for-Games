#include "ShieldCollisionComponent.h"

ShieldCollisionComponent::ShieldCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
}

void ShieldCollisionComponent::Damage(float amount)
{
	m_health -= amount;
};

void ShieldCollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	pHUD->SetShield(m_health);
	if (m_health < 0)
	{
		pHUD->SetShield(false);
		pObject->DeleteObject();
	}
};