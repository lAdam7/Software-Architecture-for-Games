#pragma once
#include "GameObject.h"

class EnemyGameObject : public GameObject
{
public:
	using GameObject::GameObject;

	void SetTarget(GameObject* pTarget);
	GameObject* GetTarget();

	void SetMaxHealth(float max);
	float GetMaxHealth();
	float GetCurrentHealth();

	void Heal();
	void Heal(float amount);
	bool IsHurt() const;
	
	void Damage(float damage);
	void SetDamage(float damage);
	float GetDamage();

	void SetDamageCooldown(float time);
	float GetDamageCooldown();

	void ResetDamageTimer();
	void AddDamageTimer(float amount);
	bool CanDamage() const;
private:
	GameObject* m_pTarget;

	float m_maxHealth = 100.0f;
	float m_currentHealth = 100.0f;

	float m_damage = 20.0f;
	float m_damageCooldown = 0.01f;
	float m_damageTimer = 0.0f;
};