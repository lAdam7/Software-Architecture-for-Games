#include "ExplosionCollisionComponent.h"
#include "AnimatedRenderComponent.h"

ExplosionCollisionComponent::ExplosionCollisionComponent(Circle2D circle, float radius, float length) : CollisionComponent(circle, radius)
{
	m_timerLength = length;
}

void ExplosionCollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());
	animate->Animate(frameTime);

	m_timer += frameTime;
	MyDrawEngine::GetInstance()->WriteDouble(400, 400, m_timer, MyDrawEngine::RED);
	if (m_timer > m_timerLength)
	{
		pObject->DeleteObject();
	}
};
/*
void CollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{

};*/