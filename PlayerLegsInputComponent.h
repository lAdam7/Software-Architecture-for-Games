#pragma once
#include "InputComponent.h"
#include "RenderComponent.h"

enum class CharState { IDLE, WALKING }; // Animation states available

/*
* Inherits from the InputComponent for the PlayerLegs
* used to detect movement around the map and the rotation
* of the player, and positioning shield if active to keep it
* always on top
*
* @author W19023403
*/
class PlayerLegsInputComponent : public InputComponent
{
private:
	// Animation state
	CharState m_state;

	// The main character / sprite with the gun
	GameObject* m_mainCharacter;

	// The shield object, if not active will be a nullptr
	GameObject* m_shield;
public:
	// Constructor, needs render component to set the animation settings
	PlayerLegsInputComponent(RenderComponent* pRender);

	// Different animations
	int idle, walk;

	// Set the main character
	void SetMainCharacter(GameObject* pObject);
	// Get the main character
	GameObject* GetMainCharacter();

	// Set the shield
	void SetShield(GameObject* pObject);
	// Get the shield
	GameObject* GetShield();

	// Override from InputComponent for detecting movement and player turning
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
};