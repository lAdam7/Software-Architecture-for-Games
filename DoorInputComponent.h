#pragma once
#include "InputComponent.h"

/*
* Inherits from the InputComponent to detect when the player
* is close to the door, if so, and the player has the keys required
* for the door, it allows you to open it, if not a message is displayed
*
* @author W19023403
*/
class DoorInputComponent : public InputComponent
{
private:
	// The amount of keys required to open this door
	int m_keysRequired;
	// The keys the player has picked-up
	int m_keysGot;
	// Player, used to detect if the player is within the radius range
	GameObject* m_pPlayer;
public:
	// Constructor set the amount of keys required to open the door
	DoorInputComponent(int keysRequired);
	// Got enough keys to open the door
	bool GotKeys() const;
	// Picked up a key for the door
	void PickedKey();

	// Set the player object, for magnitude detection
	void SetPlayer(GameObject* pPlayer);
	// Get the player object
	GameObject* GetPlayer();

	// Detecting when player is close to door and displaying messages
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;

	//void DeleteObject() override;
};