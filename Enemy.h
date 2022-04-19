#pragma once
#include "Gun.h"

enum class EnemyState { FIGHTING, IDLE, DEAD };
class Enemy: public Gun
{
private:
	EnemyState m_state;

	float m_maxHealth;
	float m_currentHealth;
	float m_regenHealth;

	float m_speed;
	float m_speedBoostRegen;
	bool m_speedBoost;

	float m_dodgePower;
	float m_dodgePowerRegen;

	float m_dropChance;

protected:

public:

};