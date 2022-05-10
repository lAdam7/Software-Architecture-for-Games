#include "DropCollisionComponent.h"
#include "PlayerLegsInputComponent.h"
#include "PlayerMainInputComponent.h"
#include "gamecode.h"

DropCollisionComponent::DropCollisionComponent(Circle2D circle, float radius, Type_Drop drop) : CollisionComponent(circle, radius)
{
	m_dropType = drop;
};

void DropCollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{

};

void DropCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pCollidedObject->getType() == Type::PLAYER)
	{
		if (m_dropType == Type_Drop::FORCEFIELD)
		{
			PlayerLegsInputComponent* pPlayerInput = dynamic_cast<PlayerLegsInputComponent*>(pCollidedObject->GetInputComponent());
			if (pPlayerInput->shield == nullptr || !pPlayerInput->shield->IsActive())
			{
				GameObject* pShieldObject = Game::instance.GetObjectManager().Create(L"Shield");
				pPlayerInput->shield = pShieldObject;
				pShieldObject->SetPosition(pCollidedObject->GetPosition());
				pHUD->SetShield(true);
			}
		}
		else if (m_dropType == Type_Drop::BOUNCING_BULLET)
		{
			PlayerLegsInputComponent* pLegsInput = dynamic_cast<PlayerLegsInputComponent*>(pCollidedObject->GetInputComponent());
			PlayerMainInputComponent* pMainInput = dynamic_cast<PlayerMainInputComponent*>(pLegsInput->mainCharacter->GetInputComponent());
			pMainInput->gun.StartSpeedBoost();
			
		}
		else if (m_dropType == Type_Drop::SHOTGUN)
		{
			PlayerLegsInputComponent* pLegsInput = dynamic_cast<PlayerLegsInputComponent*>(pCollidedObject->GetInputComponent());
			PlayerMainInputComponent* pMainInput = dynamic_cast<PlayerMainInputComponent*>(pLegsInput->mainCharacter->GetInputComponent());
			pMainInput->gun.StartShotgunBoost();
		}
		pObject->DeleteObject();
	}
};