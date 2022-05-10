#pragma once
#include "CollisionComponent.h"
#include "GameObject.h"

/*
* Inherits from the CollisionComponent for
* collision detection and removing object
* once explosion has gone far enough
*
* @author W19023403
*/
class ExplosionCollisionComponent : public CollisionComponent
{
private:
	float m_timerLength;
	float m_timer = 0;
public:
	// Constructor how long the explosion should last
	ExplosionCollisionComponent(Circle2D circle, float radius, float length);
	
	// Damage enemy if in range
	void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject) override;
	// Collision updates override
	void Update(HUD* pHUD, GameObject* pObject, float frameTime) override;
};