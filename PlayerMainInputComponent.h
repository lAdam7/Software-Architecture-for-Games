#pragma once
#include "InputComponent.h"
#include "RenderComponent.h"
#include "Gun.h"
#include "AnimatedRenderComponent.h"

/*
* Main character, always placed directly on the legs render,
* handles shooting the gun and management of bullets
*
* @author W19023403
*/
class PlayerMainInputComponent : public InputComponent
{
private:
	// The gun class, handles all the reloading times / bullet capacity
	Gun* m_gun;
	// Render component for object, easier access prevent consistent casts
	AnimatedRenderComponent* m_pAnimatedRenderComponent;
public:
	// Constructor setup the sprite animations for the top player body
	PlayerMainInputComponent(RenderComponent* pRender);

	// Get the gun that the player uses
	Gun* GetGun();

	// Set the animated render component for the player main
	void SetAnimatedRenderComponent(AnimatedRenderComponent* pRender);
	// Get the animated render component for the player main
	AnimatedRenderComponent* GetAnimatedRenderComponent();

	// Override update to listen for inputs for shooting and reloading, and updating the gun class
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
	
	// the different animations availablef or the main player
	int rifle, reload;
};
