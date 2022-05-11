#pragma once
#include "myinputs.h"
#include "HUD.h"

class GameObject;

/*
* Main InputComponent, always inherrited
* when used as different game objects need 
* to detect different inputs
*
* @author W19023403
*/
class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void Update(HUD* pHUD, GameObject* obj, float frameTime);

	// If object requires additional pointers to be removed for deletion of object
	virtual void DeleteObject();
};