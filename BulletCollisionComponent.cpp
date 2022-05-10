#include "BulletCollisionComponent.h"
#include "GameObject.h"
#include "EnemyGameObject.h"

// Constructor, use the base collision component
BulletCollisionComponent::BulletCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
};


void BulletCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pCollidedObject->GetType() == Type::ENEMY || pCollidedObject->GetType() == Type::ENEMY_BOSS)
	{
		EnemyGameObject* pEnemyGameObject = dynamic_cast<EnemyGameObject*>(pCollidedObject);
		pEnemyGameObject->Damage(100);

		pHUD->GivePoints(50);

		pObject->DeleteObject();
	}
	else if (pCollidedObject->GetType() == Type::WALL)
	{
		pObject->DeleteObject();
	}
};