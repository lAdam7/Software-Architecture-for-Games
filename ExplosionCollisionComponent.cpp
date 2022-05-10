#include "ExplosionCollisionComponent.h"
#include "AnimatedRenderComponent.h"
#include "EnemyGameObject.h"

/*
* Inherits from the CollisionComponent for
* collision detection and removing object
* once explosion has gone far enough
*
* @author W19023403
*/

// Constructor set the length of the explosion, until destroying it
ExplosionCollisionComponent::ExplosionCollisionComponent(Circle2D circle, float radius, float length) : CollisionComponent(circle, radius)
{
	m_timerLength = length;
}

// Check if timer expired, if so delete object as explosion has finished
void ExplosionCollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());
	animate->Animate(frameTime); // Update animation

	if (m_timer > m_timerLength) // timer passed, delete object
	{
		pObject->DeleteObject();
	}

	m_timer += frameTime; // increase timer
};

// Detect collisions override
void ExplosionCollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pCollidedObject->GetType() == Type::ENEMY) // Enemy within radius of explosion damage
	{
		EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pCollidedObject);
		pEnemyObject->Damage(2);
	}
};