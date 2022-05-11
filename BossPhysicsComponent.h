#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"

class BossPhysicsComponent : public PhysicsComponent
{
public:
	int idle, run, attack;

	BossPhysicsComponent(RenderComponent* pRender);
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);
};