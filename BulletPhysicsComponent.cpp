#include "BulletPhysicsComponent.h"

void BulletPhysicsComponent::Update(GameObject* pObject)
{
	pObject->SetPosition(pObject->GetPosition() + velocity);
};