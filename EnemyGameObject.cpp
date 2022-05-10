#include "EnemyGameObject.h"
#include "gamecode.h"

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
bool EnemyGameObject::IsHurt() const
{
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