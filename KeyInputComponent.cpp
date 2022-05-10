#include "KeyInputComponent.h"
#include "GameObject.h"

/*
* Inherits from the InputComponent for
* detecting when the player touches the key
* for a door
*
* @author W19023403
*/

// Constructor set the door
KeyInputComponent::KeyInputComponent(GameObject* pDoor)
{
	m_pDoor = pDoor;
};

// Get the door that the key is for
GameObject* KeyInputComponent::GetDoor()
{
	return m_pDoor;
};
