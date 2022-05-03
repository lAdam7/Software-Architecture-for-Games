#pragma once
#include "myinputs.h"

class GameObject;

class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void Update(GameObject* obj, float frameTime) = 0;
};