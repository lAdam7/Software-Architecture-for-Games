#include "ShieldCollisionComponent.h"

/*
* Inherits from the CollisionComponent,
* removes the shield once collided enough
* with the object, lost health
*
* @author W19023403
*/

// Constructor use base class collision, in CollisionComponent
ShieldCollisionComponent::ShieldCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
}

// Check if object has lost all health, if so remove
void ShieldCollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	if (pHUD->GetShield() <= 0) // Shield no health then remove
	{
		pHUD->SetShield(false);
		pObject->DeleteObject();
	}
};
