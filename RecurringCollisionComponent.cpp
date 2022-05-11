#include "RecurringCollisionComponent.h"
#include "GameObject.h"

// Constructor, use the base collision component
RecurringCollisionComponent::RecurringCollisionComponent(Rectangle2D rectangle, float x, float y) : CollisionComponent(rectangle, x, y)
{
};

void RecurringCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (/*pCollidedObject->GetType() == Type::PLAYER ||*/ pCollidedObject->GetType() == Type::ENEMY || pCollidedObject->GetType() == Type::ENEMY_BOSS)
	{
		const float COLLIDEDWIDTH = pObject->GetCollisionComponent()->GetWidth();
		const float COLLIDEDHEIGHT = pObject->GetCollisionComponent()->GetHeight();

		Vector2D newPos = pCollidedObject->GetPosition();
		// Left
		if (pCollidedObject->GetPosition().XValue < pObject->GetPosition().XValue && pCollidedObject->GetPosition().YValue < pObject->GetPosition().YValue + (COLLIDEDHEIGHT * 0.5) && pCollidedObject->GetPosition().YValue > pObject->GetPosition().YValue - (COLLIDEDHEIGHT * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(50, 100, L"L", MyDrawEngine::RED);
			newPos.XValue = (float)(pObject->GetPosition().XValue - ((COLLIDEDWIDTH * 0.5) + pCollidedObject->GetCollisionComponent()->GetRadius()));
		}
		// Right
		if (pCollidedObject->GetPosition().XValue > pObject->GetPosition().XValue && pCollidedObject->GetPosition().YValue > pObject->GetPosition().YValue - (COLLIDEDHEIGHT * 0.5) && pCollidedObject->GetPosition().YValue < pObject->GetPosition().YValue + (COLLIDEDHEIGHT * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(100, 100, L"R", MyDrawEngine::RED);
			newPos.XValue = (float)(pObject->GetPosition().XValue + ((COLLIDEDWIDTH * 0.5) + pCollidedObject->GetCollisionComponent()->GetRadius()));
		}
		// Top
		if (pCollidedObject->GetPosition().YValue > pObject->GetPosition().YValue && pCollidedObject->GetPosition().XValue > pObject->GetPosition().XValue - (COLLIDEDWIDTH * 0.5) && pCollidedObject->GetPosition().XValue < pObject->GetPosition().XValue + (COLLIDEDWIDTH * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(150, 100, L"T", MyDrawEngine::RED);
			newPos.YValue = (float)(pObject->GetPosition().YValue + ((COLLIDEDHEIGHT * 0.5) + pCollidedObject->GetCollisionComponent()->GetRadius()));
		}
		// Bottom
		if (pCollidedObject->GetPosition().YValue < pObject->GetPosition().YValue && pCollidedObject->GetPosition().XValue < pObject->GetPosition().XValue + (COLLIDEDWIDTH * 0.5) && pCollidedObject->GetPosition().XValue > pObject->GetPosition().XValue - (COLLIDEDWIDTH * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(200, 100, L"B", MyDrawEngine::RED);
			newPos.YValue = (float)(pObject->GetPosition().YValue - ((COLLIDEDHEIGHT * 0.5) + pCollidedObject->GetCollisionComponent()->GetRadius()));
		}
		pCollidedObject->SetPosition(newPos);
	}
};