#pragma once
#include "InputComponent.h"
#include "RenderComponent.h"
#include "Gun.h"

class PlayerMainInputComponent : public InputComponent
{
public:
	PlayerMainInputComponent(RenderComponent* pRender);

	Gun gun;

	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
	
	float animation = 4.0f;

	int rifle;
};
