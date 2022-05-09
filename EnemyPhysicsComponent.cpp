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


	float step = (m_rushing && m_rushingCountdown > 0.0f)
		? 320.0f * frameTime
		: 140.0f * frameTime;
	
	Vector2D a = pEnemyObject->GetTarget()->GetPosition() - pEnemyObject->GetPosition();
	float magnitude = a.magnitude();
	if (magnitude <= (step*44) || magnitude == 0.0f)
	{
		// Melee? 
		if (pAnimatedRenderComponent->GetCurrentAnimation() != attack && pEnemyObject->CanDamage())
		{
			pAnimatedRenderComponent->SetCurrentAnimation(attack);
			pEnemyObject->ResetDamageTimer();
			pHUD->SetHealth(pHUD->GetCurrentHealth() - pEnemyObject->GetDamage());
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
			if (m_moveToPos != Vector2D(0, 0))
			{
				step = 350.0f * frameTime;
				a = m_moveToPos - pEnemyObject->GetPosition();
				magnitude = a.magnitude();
				Vector2D normal = pEnemyObject->GetPosition() - m_moveToPos;
				pEnemyObject->SetAngle(atan2(-normal.YValue, normal.XValue));
				pEnemyObject->SetPosition(pEnemyObject->GetPosition() + a / magnitude * step);
				if (m_bulletAvoid == nullptr)
				{
					m_moveToPos = Vector2D(0, 0);
				}
				else
				{
					if ((pEnemyObject->GetPosition() - m_bulletAvoid->GetPosition()).magnitude() < 125.0f || m_bulletAvoidTimer > m_magnitude * .09)
					{
						m_moveToPos = Vector2D(0, 0);
					}
					m_bulletAvoidTimer += 140.0f * frameTime;
				}
			}
			else
			{
				Vector2D normal = pEnemyObject->GetPosition() - pEnemyObject->GetTarget()->GetPosition();
				pEnemyObject->SetAngle(atan2(-normal.YValue, normal.XValue));
				pEnemyObject->SetPosition(pEnemyObject->GetPosition() + a / magnitude * step);
			}	
		}
		if (m_rushing)
		{
			m_rushingCountdown -= 140.0f * frameTime;
		}
	}

	if (pEnemyObject->IsHurt())
	{
		MyDrawEngine* mDE = MyDrawEngine::GetInstance();
		Rectangle2D redBar;
		redBar.PlaceAt(pEnemyObject->GetPosition() + Vector2D(-70, 60), pEnemyObject->GetPosition() + Vector2D(70, 75));
		mDE->FillRect(redBar, MyDrawEngine::RED);

		Rectangle2D greenBar;
		float percentage = (pEnemyObject->GetCurrentHealth() / pEnemyObject->GetMaxHealth()) * 140;
		greenBar.PlaceAt(pEnemyObject->GetPosition() + Vector2D(-70, 60), pEnemyObject->GetPosition() + Vector2D(-70 + percentage, 75));
		mDE->FillRect(greenBar, MyDrawEngine::GREEN);
	}

	pEnemyObject->AddDamageTimer(frameTime);
	pAnimatedRenderComponent->Animate(frameTime);
};

void EnemyPhysicsComponent::DodgeBullet(GameObject* pObject, GameObject* pBullet)
{
	if (!m_dodgedBullet)
	{
		m_dodgedBullet = true;
		m_bulletAvoid = pBullet;
		m_bulletAvoidTimer = 0.0f;
		m_magnitude = (pObject->GetPosition() - pBullet->GetPosition()).magnitude();

		BulletPhysicsComponent* pBulletPhysics = dynamic_cast<BulletPhysicsComponent*>(pBullet->GetPhysicsComponent());

		Vector2D angle1;
		angle1.setBearing(pBulletPhysics->velocity.angle() + 1.5708f, 100.0f);

		m_moveToPos = pObject->GetPosition() + angle1;

		Circle2D circle;
		circle.PlaceAt(m_moveToPos, pObject->GetCollisionComponent()->GetRadius());
		if (!Game::instance.GetObjectManager().EnemyDirectSight(circle)) // use opposite angle
		{
			Vector2D angle2;
			angle2.setBearing(pBulletPhysics->velocity.angle() - 1.5708f, 100.0f);
			m_moveToPos = pObject->GetPosition() + angle2;
		}
	}
};

void EnemyPhysicsComponent::RushPlayer()
{
	if (!m_rushing && pAnimatedRenderComponent->GetCurrentAnimation() != idle)
	{
		m_rushing = true;
	}
};