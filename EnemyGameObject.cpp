#include "EnemyGameObject.h"
#include "gamecode.h"
#include "BulletPhysicsComponent.h"
#include "EnemyPhysicsComponent.h"
#include "AnimatedRenderComponent.h"

/*
* Inherits from the GameObject to create
* additional common properties an Enemy will
* require, containing the health management,
* damage and timers and the target of the enemy
*
* @author W19023403
*/

// Sets the target the enemy will try damage
void EnemyGameObject::SetTarget(GameObject* pTarget)
{
	m_pTarget = pTarget;
};
// Get the target of the enemy
GameObject* EnemyGameObject::GetTarget()
{
	return m_pTarget;
};

// Set the max health of the enemy
void EnemyGameObject::SetMaxHealth(float maxHealth)
{
	m_maxHealth = maxHealth;
};
// Get the max health of the enemy
float EnemyGameObject::GetMaxHealth()
{
	return m_maxHealth;
};
// Get current health of the enemy
float EnemyGameObject::GetCurrentHealth()
{
	return m_currentHealth;
};

// Is enemy hurt / taken damage
bool EnemyGameObject::IsHurt(EnemyGameObject* pEnemyObject)
{
	if (m_currentHealth != m_maxHealth)
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

	return (m_currentHealth != m_maxHealth);
};
// Enemy has been hit, decrease health
void EnemyGameObject::Damage(float damage)
{
	m_currentHealth -= damage; // damage enemy amount given
	if (m_currentHealth <= 0) // player dead
	{
		if (1 + (rand() % 100) < 90) // chance for a drop
		{
			GameObject* pDrop = Game::instance.GetObjectManager().Create(L"Drop");
			pDrop->SetPosition(GetPosition());
		}

		if (GetType() == Type::ENEMY_BOSS) // BOSS killed display completed UI
		{
			Game::instance.GetObjectManager().FreezeGame(true, Type_Freeze::WON); // Freeze the game with won message
		}

		DeleteObject(); // Remove object, enemy has died
	}
};
// Fully heal the enemy
void EnemyGameObject::Heal()
{
	m_currentHealth = m_maxHealth;
};
// Heal the enemy n amount
void EnemyGameObject::Heal(float amount)
{
	m_currentHealth += amount;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
};

// Set the damage each hit from the enemy does
void EnemyGameObject::SetDamage(float damage)
{
	m_damage = damage;
};
// Get the damage the enemy can do
float EnemyGameObject::GetDamage()
{
	return m_damage;
};

// The damage timer before hitting again
void EnemyGameObject::SetDamageCooldown(float damageCooldown)
{
	m_damageCooldown = damageCooldown;
};
// Get the damage cooldown status
float EnemyGameObject::GetDamageCooldown()
{
	return m_damageCooldown;
};

// Reset the damage timer
void EnemyGameObject::ResetDamageTimer()
{
	m_damageTimer = 0.0f;
};
// Increase the damage timer, with the frameTime
void EnemyGameObject::AddDamageTimer(float frameTime)
{
	m_damageTimer += m_damageCooldown * frameTime;
};
// Enough time has passed, so the enemy can attack again
bool EnemyGameObject::CanDamage() const
{
	return m_damageTimer > m_damageCooldown;
};

// Try dodge a bullet
void EnemyGameObject::DodgeBullet(GameObject* pObject, GameObject* pBullet)
{
	if (!m_dodgedBullet) // Not already dodged a bullet
	{
		m_dodgedBullet = true;
		m_bulletAvoid = pBullet;
		m_bulletAvoidTimer = 0.0f;
		m_magnitude = (pObject->GetPosition() - pBullet->GetPosition()).magnitude(); // distance

		BulletPhysicsComponent* pBulletPhysics = dynamic_cast<BulletPhysicsComponent*>(pBullet->GetPhysicsComponent());

		Vector2D angle1;
		angle1.setBearing(pBulletPhysics->GetVelocity().angle() + 1.5708f, 100.0f);

		m_moveToPos = pObject->GetPosition() + angle1;

		Circle2D circle;
		circle.PlaceAt(m_moveToPos, pObject->GetCollisionComponent()->GetRadius());
		if (!Game::instance.GetObjectManager().EnemyDirectSight(circle)) // use opposite angle
		{
			Vector2D angle2;
			angle2.setBearing(pBulletPhysics->GetVelocity().angle() - 1.5708f, 100.0f);
			m_moveToPos = pObject->GetPosition() + angle2;
		}
	}
};

// Start running towards the player
void EnemyGameObject::RushPlayer(GameObject* pObject)
{
	EnemyPhysicsComponent* pEnemyPhysics = dynamic_cast<EnemyPhysicsComponent*>(pObject->GetPhysicsComponent());
	AnimatedRenderComponent* pEnemyRender = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());

	if (!m_rushing && pEnemyRender->GetCurrentAnimation() != pEnemyPhysics->idle)
	{
		m_rushing = true;
	}
};

// Set if enemy has dodged a bullet or in progress
void EnemyGameObject::SetDodgedBullet(bool dodge)
{
	m_dodgedBullet = dodge;
};
// Get if enemy has dodged a bullet or in progress
bool EnemyGameObject::GetDodgedBullet() const
{
	return m_dodgedBullet;
};

// Set the position the enemy needs to move to, to avoid the bullet
void EnemyGameObject::SetMoveToPos(Vector2D position)
{
	m_moveToPos = position;
};
// Get the position the enemy needs to move to, to avoid the bullet
Vector2D EnemyGameObject::GetMoveToPos()
{
	return m_moveToPos;
};

// Set the bullet that the enemy is trying to avoid
void EnemyGameObject::SetBulletAvoid(GameObject* bullet)
{
	m_bulletAvoid = bullet;
};
// Get the bullet that the enemy is trying to avoid
GameObject* EnemyGameObject::GetBulletAvoid()
{
	return m_bulletAvoid;
};

// Set timer for how long the bullet can be avoided for
void EnemyGameObject::SetBulletAvoidTimer(float timer)
{
	m_bulletAvoidTimer = timer;
};
// Get timer for how long the bullet can be avoided for
float EnemyGameObject::GetBulletAvoidTimer()
{
	return m_bulletAvoidTimer;
};

// Set the magnitude between the player and enemy
void EnemyGameObject::SetMagnitude(float magnitude)
{
	m_magnitude = magnitude;
};
// Get the magnitude between the player and enemy
float EnemyGameObject::GetMagnitude()
{
	return m_magnitude;
};

// Set if enemy has ran at player or in progress
void EnemyGameObject::SetRushing(bool rushing)
{
	m_rushing = rushing;
};
// Get if enemy has ran at player or in progress
bool EnemyGameObject::GetRushing() const
{
	return m_rushing;
};

// Set timer for long the enemy has been rushing the player for
void EnemyGameObject::SetRushingCountdown(float countdown)
{
	m_rushingCountdown = countdown;
};
// Get timer for long the enemy has been rushing the player for
float EnemyGameObject::GetRushingCountdown()
{
	return m_rushingCountdown;
};