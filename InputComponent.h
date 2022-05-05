#pragma once
#include "myinputs.h"
#include "HUD.h"

class GameObject;

class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void Update(HUD* pHUD, GameObject* obj, float frameTime) = 0;
};