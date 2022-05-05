#pragma once
#include "mydrawengine.h"

class HUD
{
private:
	bool m_active;

	int m_points;

	float m_maxHealth;
	float m_currentHealth;

	int m_maxAmmo;
	int m_currentAmmo;
	float m_ReloadProgress;
	
	float m_maxShield;
	float m_currentShield;
public:
	HUD();

	void SetActive(bool activity);
	bool IsActive();

	void Update();

	int GetPoints();
	void GivePoints(int amount);
	bool SpendPoints(int amount);

	void SetMaxHealth(float health);
	void SetHealth(float health);
	void Heal(float amount);
	void Heal();
	float GetMaxHealth();
	float GetCurrentHealth();

	void SetMaxAmmo(int ammo);
	void SetAmmo(int ammo);
	void Reload(int amount);
	void Reload();
	int GetMaxAmmo();
	int GetCurrentAmmo();
	void SetReloadProgress(float progress);
	float GetReloadProgress();

	void SetMaxShield(float amount);
	void SetShield(float amount);
	int GetMaxShield();
	int GetShield();
};