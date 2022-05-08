#include "KeyInputComponent.h"
#include "GameObject.h"

KeyInputComponent::KeyInputComponent(GameObject* pDoor)
{
	m_pDoor = pDoor;
};

GameObject* KeyInputComponent::GetDoor()
{
	return m_pDoor;
}

void KeyInputComponent::Update(HUD* pHUD, GameObject* obj, float frameTime)
{

};