#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"

class EnemyPhysicsComponent : public PhysicsComponent
{
public:
	int rifle;

	EnemyPhysicsComponent(RenderComponent* pRender);
	void Update(GameObject* pObject);
};