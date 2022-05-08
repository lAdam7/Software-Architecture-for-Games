#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

class ExplosionCollisionComponent : public CollisionComponent
{
private:
	float m_timerLength;
	float m_timer = 0;
public:
	//using CollisionComponent::CollisionComponent;
	ExplosionCollisionComponent(Circle2D circle, float radius, float length) ;
	//CollisionComponent(shape, radius);
	void Update(GameObject* pObject, float frameTime);
	//void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject);
};