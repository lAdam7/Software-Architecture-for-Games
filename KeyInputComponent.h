#pragma once
#include "InputComponent.h"

/*
* Inherits from the InputComponent for
* detecting when the player touches the key
* for a door
*
* @author W19023403
*/
class KeyInputComponent : public InputComponent
{
private:
	// The door the key is for
	GameObject* m_pDoor;
public:
	// Constructor, set the door the key is for
	KeyInputComponent(GameObject* pDoor);

	// Get the door the key is for
	GameObject* GetDoor();
};