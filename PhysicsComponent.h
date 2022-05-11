#pragma once
#include "HUD.h"

class GameObject;

/*
* PhysicsComponent, used mostly for enemy AI aspects
* in this game, and bullet velocity, etc. This class
* is more of a general/misc than directly physics related
* due to it being a small game, always inherited as objects
* will always have different physic components
*
* @author W19023403
*/
class PhysicsComponent
{
public:
	// Destructor
	virtual ~PhysicsComponent();

	// Update physics in child class
	virtual void Update(HUD* pHUD, GameObject* obj, float frameTime) = 0;

	// If object requires additional pointers to be removed for deletion of object
	virtual void DeleteObject();
};