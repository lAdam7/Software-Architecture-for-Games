#include "EnemyMessageComponent.h"
#include "EnemyPhysicsComponent.h"
#include "BulletPhysicsComponent.h"

void EnemyMessageComponent::HandleMessage(GameObject* pObject, Message& message)
{
	if (message.type == EventType::BULLET_FIRED)
	{
		EnemyPhysicsComponent* pEnemyPhysics = dynamic_cast<EnemyPhysicsComponent*>(pObject->GetPhysicsComponent());
		BulletPhysicsComponent* pBulletPhysics = dynamic_cast<BulletPhysicsComponent*>(message.pSource->GetPhysicsComponent());

		if (pEnemyPhysics->pAnimatedRenderComponent->GetCurrentAnimation() != pEnemyPhysics->idle)
		{
			float magnitude = (pObject->GetPosition() - message.pSource->GetPosition()).magnitude() * 2;

			Vector2D angle;
			angle.setBearing(pBulletPhysics->velocity.angle(), magnitude);

			Segment2D intersectLine;
			intersectLine.PlaceAt(message.pSource->GetPosition(), message.pSource->GetPosition() + angle);

			if (pObject->GetCollisionComponent()->GetShape(pObject).Intersects(intersectLine))
			{
				pEnemyPhysics->DodgeBullet(pObject, message.pSource); // Tell enemy to avoid, if they can
			}
		}
	}
	else if (message.type == EventType::CHARACTER_IS_RELOADING)
	{
		EnemyPhysicsComponent* pEnemyPhysics = dynamic_cast<EnemyPhysicsComponent*>(pObject->GetPhysicsComponent());
		pEnemyPhysics->RushPlayer();
	}
};