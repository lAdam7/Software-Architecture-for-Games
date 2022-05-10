#include "EnemyCollisionComponent.h"
#include "GameObject.h"

// Constructor, use the base collision component
EnemyCollisionComponent::EnemyCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
};


void EnemyCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pCollidedObject->GetType() == Type::ENEMY || pCollidedObject->GetType() == Type::SHIELD || pCollidedObject->GetType() == Type::PLAYER)
	{
		float dx = pCollidedObject->GetPosition().XValue - pObject->GetPosition().XValue;
		float dy = pCollidedObject->GetPosition().YValue - pObject->GetPosition().YValue;

		float dist = sqrt(dx * dx + dy * dy);

		float nx = dx / dist;
		float ny = dy / dist;

		float touchDistFromB1 = (dist * (pObject->GetCollisionComponent()->GetRadius() / (pObject->GetCollisionComponent()->GetRadius() + pCollidedObject->GetCollisionComponent()->GetRadius())));
		float contactX = pObject->GetPosition().XValue + nx * touchDistFromB1;
		float contactY = pObject->GetPosition().YValue + ny * touchDistFromB1;

		pObject->SetPosition(Vector2D(contactX - nx * pObject->GetCollisionComponent()->GetRadius(), contactY - ny * pObject->GetCollisionComponent()->GetRadius()));
	}
};