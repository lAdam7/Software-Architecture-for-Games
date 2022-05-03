#pragma once
#include "PhysicsComponent.h"
#include "GameObject.h"

class BulletPhysicsComponent : public PhysicsComponent
{
public:
	Vector2D velocity;
	void Update(GameObject* pObject);
};