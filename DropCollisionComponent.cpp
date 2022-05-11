#include "DropCollisionComponent.h"
#include "PlayerLegsInputComponent.h"
#include "PlayerMainInputComponent.h"
#include "gamecode.h"

/*
* Inherits from the CollisionComponent to handle collisions
*
* @author W19023403
*/

// Constructor set the drop type, and call the CollisionComponent values
DropCollisionComponent::DropCollisionComponent(Circle2D circle, float radius, Type_Drop drop) : CollisionComponent(circle, radius)
{
	m_dropType = drop;
};

// Collision with another collidable object
void DropCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pCollidedObject->GetType() == Type::PLAYER) // Drop collides with the Player
	{
		if (m_dropType == Type_Drop::FORCEFIELD) // Create forcefield
		{
			PlayerLegsInputComponent* pPlayerInput = dynamic_cast<PlayerLegsInputComponent*>(pCollidedObject->GetInputComponent());
			if (pPlayerInput->GetShield() != nullptr)
			{
				pPlayerInput->GetShield()->DeleteObject();
			}
			GameObject* pShieldObject = Game::instance.GetObjectManager().Create(L"Shield"); // Create shield
			pPlayerInput->SetShield(pShieldObject); // Let player know of the shield, to keep position always directly on-top of the player
			pShieldObject->SetPosition(pCollidedObject->GetPosition());
			pHUD->SetShield(true); // Show UI

		}
		else if (m_dropType == Type_Drop::BOUNCING_BULLET) // Create speed boost / infinite ammo
		{
			PlayerLegsInputComponent* pLegsInput = dynamic_cast<PlayerLegsInputComponent*>(pCollidedObject->GetInputComponent());
			PlayerMainInputComponent* pMainInput = dynamic_cast<PlayerMainInputComponent*>(pLegsInput->GetMainCharacter()->GetInputComponent());
			pMainInput->GetGun()->StartSpeedBoost(); // Call the gun for the player and start the timer / perks of infinite ammo and speed boost
			
		}
		else if (m_dropType == Type_Drop::SHOTGUN) // Create shotgun effect
		{
			PlayerLegsInputComponent* pLegsInput = dynamic_cast<PlayerLegsInputComponent*>(pCollidedObject->GetInputComponent());
			PlayerMainInputComponent* pMainInput = dynamic_cast<PlayerMainInputComponent*>(pLegsInput->GetMainCharacter()->GetInputComponent());
			pMainInput->GetGun()->StartShotgunBoost(); // Call the gun for the player and start the timer / perks for multi shots at once
		}
		pObject->DeleteObject(); // Delete drop, it's been picked up
	}
};