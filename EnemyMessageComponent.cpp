#include "EnemyMessageComponent.h"
#include "EnemyGameObject.h"
#include "EnemyPhysicsComponent.h"
#include "BulletPhysicsComponent.h"

/*
* Inherits from the MessageComponent for
* sending messages to a enemy
*
* @author W19023403
*/

// Receive message from another object
void EnemyMessageComponent::HandleMessage(GameObject* pObject, Message& message)
{
	if (message.type == EventType::BULLET_FIRED) // The player has fired a bullet
	{
		EnemyGameObject* pEnemyGameObject = dynamic_cast<EnemyGameObject*>(pObject);
		EnemyPhysicsComponent* pEnemyPhysics = dynamic_cast<EnemyPhysicsComponent*>(pObject->GetPhysicsComponent());
		BulletPhysicsComponent* pBulletPhysics = dynamic_cast<BulletPhysicsComponent*>(message.pSource->GetPhysicsComponent());

		if (pEnemyPhysics->pAnimatedRenderComponent->GetCurrentAnimation() != pEnemyPhysics->idle) // Player isn't idle, so currently targetting the player
		{
			float magnitude = (pObject->GetPosition() - message.pSource->GetPosition()).magnitude() * 2; // Distance between the created bullet and the enemy *2 for safety

			Vector2D angle;
			angle.setBearing(pBulletPhysics->velocity.angle(), magnitude); // Same angle of the bullet, add the magnitude

			Segment2D intersectLine;
			intersectLine.PlaceAt(message.pSource->GetPosition(), message.pSource->GetPosition() + angle); // Place in a line, to check for intersection

			// Line intersects the enemy, (the bullet will hit the player)
			if (pObject->GetCollisionComponent()->GetShape(pObject).Intersects(intersectLine))
			{
				pEnemyGameObject->DodgeBullet(pObject, message.pSource); // Tell enemy to avoid, if they can (haven't done it before)
			}
		}
	}
	else if (message.type == EventType::CHARACTER_IS_RELOADING) // The player is reloading
	{
		EnemyGameObject* pEnemyGameObject = dynamic_cast<EnemyGameObject*>(pObject);
		pEnemyGameObject->RushPlayer(pObject); // Enemy will run faster to the player, if they haven't already used the ability
	}
};