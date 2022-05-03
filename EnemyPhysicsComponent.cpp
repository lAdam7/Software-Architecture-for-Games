#include "EnemyPhysicsComponent.h"
#include "AnimatedRenderComponent.h"
#include "EnemyGameObject.h"


EnemyPhysicsComponent::EnemyPhysicsComponent(RenderComponent* pRender)
{
	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pRender);

	rifle = animate->NewAnimation();
	animate->AddImage(rifle, L"survivorRifle_0.png");
	animate->AddImage(rifle, L"survivorRifle_1.png");
	animate->AddImage(rifle, L"survivorRifle_2.png");
	animate->AddImage(rifle, L"survivorRifle_3.png");
	animate->AddImage(rifle, L"survivorRifle_4.png");
	animate->AddImage(rifle, L"survivorRifle_5.png");
	animate->AddImage(rifle, L"survivorRifle_6.png");
	animate->AddImage(rifle, L"survivorRifle_7.png");
	animate->AddImage(rifle, L"survivorRifle_8.png");
	animate->AddImage(rifle, L"survivorRifle_9.png");
	animate->AddImage(rifle, L"survivorRifle_10.png");
	animate->AddImage(rifle, L"survivorRifle_11.png");
	animate->AddImage(rifle, L"survivorRifle_12.png");
	animate->AddImage(rifle, L"survivorRifle_13.png");
	animate->AddImage(rifle, L"survivorRifle_14.png");
	animate->AddImage(rifle, L"survivorRifle_15.png");
	animate->AddImage(rifle, L"survivorRifle_16.png");
	animate->AddImage(rifle, L"survivorRifle_17.png");
	animate->AddImage(rifle, L"survivorRifle_18.png");
	animate->AddImage(rifle, L"survivorRifle_19.png");

	animate->SetCurrentAnimation(rifle);
}

void EnemyPhysicsComponent::Update(GameObject* pObject)
{
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pObject);
	MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	mDE->DrawLine(pEnemyObject->GetPosition(), pEnemyObject->pTarget->GetPosition(), MyDrawEngine::WHITE);

	float step = 1.0f;
	
	Vector2D a = pEnemyObject->pTarget->GetPosition() - pEnemyObject->GetPosition();
	float magnitude = a.magnitude();
	if (magnitude <= step || magnitude == 0.0f)
	{
		// Melee? 
	}
	else
	{
		pEnemyObject->SetPosition(pEnemyObject->GetPosition() + a / magnitude * step);
	}

};