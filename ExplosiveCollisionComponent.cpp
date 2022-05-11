#include "ExplosiveCollisionComponent.h"
#include "GameObject.h"
#include "gamecode.h"

/*
* Inherits from the CollisionComponent for
* collision detection of a bullet hitting the
* explosive
*
* @author W19023403
*/

// Constructor, use the base collision component
ExplosiveCollisionComponent::ExplosiveCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
};

// Bullet hit explosive
void ExplosiveCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pCollidedObject->GetType() == Type::BULLET) // Collided with a bullet
	{
		GameObject* pExplosion = Game::instance.GetObjectManager().Create(L"Explosion"); // Create explosion
		pExplosion->SetPosition(pObject->GetPosition());
		
		Game::instance.GetObjectManager().GetSoundFX()->PlayExplosion(); // Play explosion sound

		pObject->DeleteObject();
	}
};