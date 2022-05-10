#include "ShieldCollisionComponent.h"

ShieldCollisionComponent::ShieldCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
	
}

void ShieldCollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	if (pHUD->GetShield() <= 0)
	{
		pHUD->SetShield(false);
		pObject->DeleteObject();
	}
};
