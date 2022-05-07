#include "BulletPhysicsComponent.h"

void BulletPhysicsComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	pObject->SetPosition(pObject->GetPosition() + velocity * frameTime);

	//m_timer = m_timer - frameTime;
	if (m_timer < 0)
	{
		pObject->DeleteObject();
	}
};