#include "KeyCollisionComponent.h"
#include "GameObject.h"
#include "KeyInputComponent.h"
#include "DoorInputComponent.h"

/*
* Inherits from the CollisionComponent for
* collision detection for when a player
* touches the key
*
* @author W19023403
*/


KeyCollisionComponent::KeyCollisionComponent(Circle2D circle, float radius) : CollisionComponent(circle, radius)
{
};


void KeyCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pCollidedObject->GetType() == Type::PLAYER)
	{
		KeyInputComponent* pKeyInput = dynamic_cast<KeyInputComponent*>(pObject->GetInputComponent());
		DoorInputComponent* pDoorInput = dynamic_cast<DoorInputComponent*>(pKeyInput->GetDoor()->GetInputComponent());
		pDoorInput->PickedKey();
		pObject->DeleteObject();
	}
};