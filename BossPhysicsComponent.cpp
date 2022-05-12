#include "BossPhysicsComponent.h"
#include "EnemyGameObject.h"
#include "gamecode.h"
#include "BulletPhysicsComponent.h"
#include "vector2D.h"

/*
* Inherits from the PhysicsComponent, setups the
* various boss animations, keeps updated and determines
* on attacking player and damages
*
* @author W19023403
*/

// Constructor setup the animations for the boss
BossPhysicsComponent::BossPhysicsComponent(RenderComponent* pRender)
{
	AnimatedRenderComponent* pAnimatedRenderComponent = dynamic_cast<AnimatedRenderComponent*>(pRender);

	run = pAnimatedRenderComponent->NewAnimation();
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_0.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_1.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_2.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_3.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_4.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_5.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_6.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_7.png");
	pAnimatedRenderComponent->AddImage(run, L"boss_walk_8.png");
	pAnimatedRenderComponent->NextAnimation(run, run);
	pAnimatedRenderComponent->SetAnimationSpeed(run, 8.0f);

	idle = pAnimatedRenderComponent->NewAnimation();
	pAnimatedRenderComponent->AddImage(idle, L"boss_walk_0.png");
	pAnimatedRenderComponent->NextAnimation(idle, idle);
	pAnimatedRenderComponent->SetAnimationSpeed(idle, 7.0f);
	pAnimatedRenderComponent->SetCurrentAnimation(idle);

	attack = pAnimatedRenderComponent->NewAnimation();
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_0.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_1.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_2.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_3.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_4.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_5.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_6.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_7.png");
	pAnimatedRenderComponent->AddImage(attack, L"boss_attack_8.png");
	pAnimatedRenderComponent->NextAnimation(attack, run);
	pAnimatedRenderComponent->SetAnimationSpeed(attack, 7.0f);
};

// Checking if can target player, if so running towards
void BossPhysicsComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pObject);
	AnimatedRenderComponent* pAnimatedRenderComponent = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());

	// Should the enemy be rushing the player
	float step = (pEnemyObject->GetRushing() && pEnemyObject->GetRushingCountdown() > 0.0f)
		? 320.0f * frameTime
		: 140.0f * frameTime;

	// Distance between the two vectors, get magnitude
	Vector2D pos = pEnemyObject->GetTarget()->GetPosition() - pEnemyObject->GetPosition();
	float magnitude = pos.magnitude();

	// Enemy still in idle state, check if the enemy can see the player/target if so set animation to run
	if (pAnimatedRenderComponent->GetCurrentAnimation() == idle)
	{
		Segment2D line;
		line.PlaceAt(pEnemyObject->GetPosition(), pEnemyObject->GetTarget()->GetPosition());
		bool sight = Game::instance.GetObjectManager().EnemyDirectSight(line);
		if (sight)
		{
			pAnimatedRenderComponent->SetCurrentAnimation(run);
		}

	}
	else // running or fighting animation
	{
		// Avoiding a bullet fired at the enemy
		if (pEnemyObject->GetMoveToPos() != Vector2D(0, 0))
		{
			step = 350.0f * frameTime;
			pos = pEnemyObject->GetMoveToPos() - pEnemyObject->GetPosition();
			magnitude = pos.magnitude();

			// Towards the target point
			Vector2D normal = pEnemyObject->GetPosition() - pEnemyObject->GetMoveToPos();
			pEnemyObject->SetAngle(atan2(-normal.YValue, normal.XValue));
			pEnemyObject->SetPosition(pEnemyObject->GetPosition() + pos / magnitude * step);

			if (pEnemyObject->GetBulletAvoid() == nullptr) // Bullet already gone, reset pos to start targetting player again
			{
				pEnemyObject->SetMoveToPos(Vector2D(0, 0));
			}
			else // Still avoiding a bullet
			{
				// Bullet shoud have already passed the enemy, start targetting player again
				if ((pEnemyObject->GetPosition() - pEnemyObject->GetBulletAvoid()->GetPosition()).magnitude() < 125.0f || pEnemyObject->GetBulletAvoidTimer() > pEnemyObject->GetMagnitude() * .09)
				{
					pEnemyObject->SetMoveToPos(Vector2D(0, 0));
				}
				// Update bullet avoidance, for next iteration check
				pEnemyObject->SetBulletAvoidTimer(pEnemyObject->GetBulletAvoidTimer() + 140.0f * frameTime);
			}
		}
		else // not avoiding a bullet, target the player
		{
			// Towards the player position
			Vector2D normal = pEnemyObject->GetPosition() - pEnemyObject->GetTarget()->GetPosition();
			pEnemyObject->SetAngle(atan2(-normal.YValue, normal.XValue));
			pEnemyObject->SetPosition(pEnemyObject->GetPosition() + pos / magnitude * step);
		}
	}
	// Enemy is currently rushing the player, decrease timer to check for when rushing has expired
	if (pEnemyObject->GetRushing())
	{
		pEnemyObject->SetRushingCountdown(pEnemyObject->GetRushingCountdown() - 140.0f * frameTime);
	}
	
	// Checks if enemy is hurt, if so it draws a health bar above the player
	pEnemyObject->IsHurt(pEnemyObject);

	// Since last hit
	pEnemyObject->AddDamageTimer(frameTime);

	// Update animation
	pAnimatedRenderComponent->Animate(frameTime);
};