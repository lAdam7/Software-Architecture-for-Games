#include "EnemyGameObject.h"
#include "gamecode.h"

void EnemyGameObject::SetTarget(GameObject* pTarget)
{
	m_pTarget = pTarget;
};
GameObject* EnemyGameObject::GetTarget()
{
	return m_pTarget;
};

void EnemyGameObject::SetMaxHealth(float maxHealth)
{
	m_maxHealth = maxHealth;
};
float EnemyGameObject::GetMaxHealth()
{
	return m_maxHealth;
};

float EnemyGameObject::GetCurrentHealth()
{
	return m_currentHealth;
}

bool EnemyGameObject::IsHurt() const
{
	return (m_currentHealth != m_maxHealth);
};
void EnemyGameObject::Damage(float damage)
{
	m_currentHealth -= damage;
	if (m_currentHealth <= 0)
	{
		//GameObject* pB = Game::instance.GetObjectManager().Create(L"Enemy1");
		//EnemyGameObject* pTest = dynamic_cast<EnemyGameObject*>(pB);
		
		//pTest->SetTarget(m_pTarget);

		DeleteObject();
	}
}
void EnemyGameObject::Heal()
{
	m_currentHealth = m_maxHealth;
};
void EnemyGameObject::Heal(float amount)
{
	m_currentHealth += amount;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
};

void EnemyGameObject::SetDamage(float damage)
{
	m_damage = damage;
};
float EnemyGameObject::GetDamage()
{
	return m_damage;
};

void EnemyGameObject::SetDamageCooldown(float damageCooldown)
{
	m_damageCooldown = damageCooldown;
};
float EnemyGameObject::GetDamageCooldown()
{
	return m_damageCooldown;
};

void EnemyGameObject::ResetDamageTimer()
{
	m_damageTimer = 0.0f;
};
void EnemyGameObject::AddDamageTimer(float frameTime)
{
	m_damageTimer += m_damageCooldown * frameTime;
};
bool EnemyGameObject::CanDamage() const
{
	return m_damageTimer > m_damageCooldown;
};