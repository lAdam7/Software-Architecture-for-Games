#pragma once
#include "InputComponent.h"

class DoorInputComponent : public InputComponent
{
public:
	DoorInputComponent(int keysRequired);
	bool GotKeys() const;
	void PickedKey();
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);
	GameObject* pPlayer;
private:
	int m_keysRequired;
	int m_keysGot = 0;
};