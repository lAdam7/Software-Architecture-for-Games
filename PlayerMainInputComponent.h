#pragma once
#include "InputComponent.h"
#include "RenderComponent.h"
#include "Gun.h"
#include "AnimatedRenderComponent.h"

class PlayerMainInputComponent : public InputComponent
{
public:
	PlayerMainInputComponent(RenderComponent* pRender);

	Gun gun;

	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
	
	AnimatedRenderComponent* pAnimatedRenderComponent;

	float animation = 4.0f;

	int rifle, reload;
};
