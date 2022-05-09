#pragma once
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"

class EnemyPhysicsComponent : public PhysicsComponent
{
private:
	bool m_dodgedBullet = false;
	Vector2D m_moveToPos;
	GameObject* m_bulletAvoid;
	bool m_bulletPassing = false;
	float m_bulletAvoidTimer;
	float m_magnitude;
	bool m_rushing = false;
	float m_rushingCountdown = 200.0f;
public:
	int idle, run, attack;
	AnimatedRenderComponent* pAnimatedRenderComponent;

	EnemyPhysicsComponent(RenderComponent* pRender);
	void Update(HUD* pHUD, GameObject* pObject, float frameTime);
	void DodgeBullet(GameObject* pObject, GameObject* pBullet);
	void RushPlayer();
};