#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"

/*
* Inherits from the PhysicsComponent, setups the
* various boss animations, keeps updated and determines
* on attacking player and damages
*
* @author W19023403
*/
class BossPhysicsComponent : public PhysicsComponent
{
public:
	// The various animations the boss has
	int idle, run, attack;
	// Constructor setup the animations for the boss
	BossPhysicsComponent(RenderComponent* pRender);
	// Checking if can target player, if so running towards
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);
};