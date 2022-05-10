#pragma once
#include "GameObject.h"

/*
* Inherits from the GameObject to create
* additional common properties an Enemy will
* require, containing the health management, 
* damage and timers and the target of the enemy
*
* @author W19023403
*/
class EnemyGameObject : public GameObject
{
private:
	GameObject* m_pTarget;

	float m_maxHealth = 100.0f;
	float m_currentHealth = 100.0f;

	float m_damage = 20.0f;
	float m_damageCooldown = 0.01f;
	float m_damageTimer = 0.0f;
public:
	using GameObject::GameObject;

	// Set target the enemy will aim to damage
	void SetTarget(GameObject* pTarget);
	// Get the target of the enemy
	GameObject* GetTarget();

	// The max health of the enemy
	void SetMaxHealth(float max);
	// Get the max health of the enemy
	float GetMaxHealth();
	// Get the current health of the enemy
	float GetCurrentHealth();

	// Heal the enemy
	void Heal();
	// Heal the enemy a specific amount
	void Heal(float amount);
	// Enemy taken damage
	bool IsHurt() const;
	
	// Damage the enemy
	void Damage(float damage);
	// The damage the enemy does per hit
	void SetDamage(float damage);
	// The damage the enemy does
	float GetDamage();

	// How frequently the enemy can damage the player
	void SetDamageCooldown(float time);
	// Get current cooldown timer
	float GetDamageCooldown();
	// Reset the timer, for rehits
	void ResetDamageTimer();
	// Increment damage timer, ready for next hit
	void AddDamageTimer(float amount);
	// Enough time passed to damage again
	bool CanDamage() const;
};