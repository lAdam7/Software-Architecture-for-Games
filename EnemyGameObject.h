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

	bool m_dodgedBullet = false;
	Vector2D m_moveToPos;
	GameObject* m_bulletAvoid;
	float m_bulletAvoidTimer;
	float m_magnitude;
	bool m_rushing = false;
	float m_rushingCountdown = 200.0f;
	
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
	bool IsHurt(EnemyGameObject* pEnemyObject);
	
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

	// Try dodge a bullet
	void DodgeBullet(GameObject* pObject, GameObject* pBullet);
	// Start running towards the player
	void RushPlayer(GameObject* pObject);

	// Set if enemy has dodged a bullet or in progress
	void SetDodgedBullet(bool dodge);
	// Get if enemy has dodged a bullet or in progress
	bool GetDodgedBullet() const;
	// Set the position the enemy needs to move to, to avoid the bullet
	void SetMoveToPos(Vector2D position);
	// Get the position the enemy needs to move to, to avoid the bullet
	Vector2D GetMoveToPos();
	// Set the bullet that the enemy is trying to avoid
	void SetBulletAvoid(GameObject* bullet);
	// Get the bullet that the enemy is trying to avoid
	GameObject* GetBulletAvoid();
	// Set timer for how long the bullet can be avoided for
	void SetBulletAvoidTimer(float timer);
	// Get timer for how long the bullet can be avoided for
	float GetBulletAvoidTimer();
	// Set the magnitude between the player and enemy
	void SetMagnitude(float magnitude);
	// Get the magnitude between the player and enemy
	float GetMagnitude();
	// Set if enemy has ran at player or in progress
	void SetRushing(bool rush);
	// Get if enemy has ran at player or in progress
	bool GetRushing() const;
	// Set timer for long the enemy has been rushing the player for
	void SetRushingCountdown(float countdown);
	// Get timer for long the enemy has been rushing the player for
	float GetRushingCountdown();
};