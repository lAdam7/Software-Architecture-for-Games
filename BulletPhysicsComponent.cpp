#include "BulletPhysicsComponent.h"

void BulletPhysicsComponent::Update(GameObject* pObject)
{
	pObject->SetPosition(pObject->GetPosition() + velocity);

	//m_timer = m_timer - frameTime;
	if (m_timer < 0)
	{
		pObject->DeleteObject();
	}
};