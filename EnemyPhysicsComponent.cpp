#include "EnemyPhysicsComponent.h"
#include "EnemyGameObject.h"
#include "gamecode.h"
#include "BulletPhysicsComponent.h"

/*
* Inherits from the PhysicsComponent, setups the
* various enemy animations, keeps updated and determines
* on attacking player and damages
*
* @author W19023403
*/

// Constructor setup the animations for the enemy
EnemyPhysicsComponent::EnemyPhysicsComponent(RenderComponent* pRender)
{
	AnimatedRenderComponent* pAnimatedRenderComponent = dynamic_cast<AnimatedRenderComponent*>(pRender);

	run = pAnimatedRenderComponent->NewAnimation(); // run
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_0.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_1.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_2.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_3.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_4.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_5.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_6.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_7.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_8.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_9.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_10.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_11.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_12.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_13.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_14.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_15.png");
	pAnimatedRenderComponent->AddImage(run, L"skeleton-move_16.png");

	pAnimatedRenderComponent->NextAnimation(run, run);
	pAnimatedRenderComponent->SetAnimationSpeed(run, 10.0f);

	idle = pAnimatedRenderComponent->NewAnimation(); // idle
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_0.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_1.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_2.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_3.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_4.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_5.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_6.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_7.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_8.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_9.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_10.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_11.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_12.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_13.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_14.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_15.png");
	pAnimatedRenderComponent->AddImage(idle, L"skeleton-idle_16.png");

	pAnimatedRenderComponent->NextAnimation(idle, idle);
	pAnimatedRenderComponent->SetAnimationSpeed(idle, 10.0f);
	pAnimatedRenderComponent->SetCurrentAnimation(idle);

	attack = pAnimatedRenderComponent->NewAnimation(); // attack
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_0.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_1.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_2.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_3.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_4.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_5.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_6.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_7.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_8.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_7.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_6.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_5.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_4.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_3.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_2.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_1.png");
	pAnimatedRenderComponent->AddImage(attack, L"skeleton-attack_0.png");

	pAnimatedRenderComponent->NextAnimation(attack, run);
	pAnimatedRenderComponent->SetAnimationSpeed(attack, 10.0f);
};

// Checking if can target player, if so running towards
void EnemyPhysicsComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
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
	float stepMultiplier = (pHUD->GetShield() > 0.0f) ? 56.0f : 34.0f;

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

			// Bullet already gone, reset pos to start targetting player again
			if (pEnemyObject->GetBulletAvoid() == nullptr)
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