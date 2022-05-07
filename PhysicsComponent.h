#pragma once
#include "HUD.h"

class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent();
	virtual void Update(HUD* pHUD, GameObject* obj, float frameTime);
};