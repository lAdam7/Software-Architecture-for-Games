#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"

class EnemyPhysicsComponent : public PhysicsComponent
{
public:
	int idle, run, attack;
	AnimatedRenderComponent* pAnimatedRenderComponent;

	EnemyPhysicsComponent(RenderComponent* pRender);
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);
};