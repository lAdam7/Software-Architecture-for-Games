#include "InputComponent.h"
#include "GameObject.h"

/*
* Main InputComponent, always inherrited
* when used as different game objects need
* to detect different inputs
*
* @author W19023403
*/

// Constructor
InputComponent::InputComponent()
{
};

// Destructor
InputComponent::~InputComponent()
{
};

void InputComponent::Update(HUD* pHUD, GameObject* obj, float frameTime)
{

};