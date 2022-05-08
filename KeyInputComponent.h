#pragma once
#include "InputComponent.h"

class KeyInputComponent : public InputComponent
{
public:
	KeyInputComponent(GameObject* pDoor);
	GameObject* GetDoor();
	void Update(HUD* pHUD, GameObject* obj, float frameTime);
private:
	GameObject* m_pDoor;
};