#include "EnemyPhysicsComponent.h"
#include "EnemyGameObject.h"
#include "gamecode.h"
#include "BulletPhysicsComponent.h"

EnemyPhysicsComponent::EnemyPhysicsComponent(RenderComponent* pRender)
{
	pAnimatedRenderComponent = dynamic_cast<AnimatedRenderComponent*>(pRender);

	run = pAnimatedRenderComponent->NewAnimation();
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

	idle = pAnimatedRenderComponent->NewAnimation();
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

	attack = pAnimatedRenderComponent->NewAnimation();
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

void EnemyPhysicsComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pObject);

	float step = (pEnemyObject->GetRushing() && pEnemyObject->GetRushingCountdown() > 0.0f)
		? 320.0f * frameTime
		: 140.0f * frameTime;
	
	Vector2D a = pEnemyObject->GetTarget()->GetPosition() - pEnemyObject->GetPosition();
	float magnitude = a.magnitude();
	float stepMultiplier = (pHUD->GetShield() > 0.0f) ? 56.0f : 40.0f;
	if (magnitude <= (step*stepMultiplier) || magnitude == 0.0f)
	{
		// Melee? 
		if (pAnimatedRenderComponent->GetCurrentAnimation() != attack && pEnemyObject->CanDamage())
		{
			pAnimatedRenderComponent->SetCurrentAnimation(attack);
			pEnemyObject->ResetDamageTimer();
			if (pHUD->GetShield() > 0.0f)
			{
				pHUD->SetShield(pHUD->GetShield() - pEnemyObject->GetDamage());
			}
			else
			{
				pHUD->SetHealth(pHUD->GetCurrentHealth() - pEnemyObject->GetDamage());
			}
		}
	}
	else
	{
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
		else
		{
			if (pEnemyObject->GetMoveToPos() != Vector2D(0, 0))
			{
				step = 350.0f * frameTime;
				a = pEnemyObject->GetMoveToPos() - pEnemyObject->GetPosition();
				magnitude = a.magnitude();
				Vector2D normal = pEnemyObject->GetPosition() - pEnemyObject->GetMoveToPos();
				pEnemyObject->SetAngle(atan2(-normal.YValue, normal.XValue));
				pEnemyObject->SetPosition(pEnemyObject->GetPosition() + a / magnitude * step);
				if (pEnemyObject->GetBulletAvoid() == nullptr)
				{
					pEnemyObject->SetMoveToPos(Vector2D(0, 0));
				}
				else
				{
					if ((pEnemyObject->GetPosition() - pEnemyObject->GetBulletAvoid()->GetPosition()).magnitude() < 125.0f || pEnemyObject->GetBulletAvoidTimer() > pEnemyObject->GetMagnitude() * .09)
					{
						pEnemyObject->SetMoveToPos(Vector2D(0, 0));
					}
					pEnemyObject->SetBulletAvoidTimer(pEnemyObject->GetBulletAvoidTimer() + 140.0f * frameTime);
				}
			}
			else
			{
				Vector2D normal = pEnemyObject->GetPosition() - pEnemyObject->GetTarget()->GetPosition();
				pEnemyObject->SetAngle(atan2(-normal.YValue, normal.XValue));
				pEnemyObject->SetPosition(pEnemyObject->GetPosition() + a / magnitude * step);
			}	
		}
		if (pEnemyObject->GetRushing())
		{
			pEnemyObject->SetRushingCountdown(pEnemyObject->GetRushingCountdown() - 140.0f * frameTime);
		}
	}

	pEnemyObject->IsHurt(pEnemyObject);

	pEnemyObject->AddDamageTimer(frameTime);
	pAnimatedRenderComponent->Animate(frameTime);
};