#pragma once

/*
* Main HUD for the player, shows the users
* current points, alongside the health status,
* ammo status and the active shield if active
*
* @author W19023403
*/
class HUD
{
private:
	// Render the HUD
	bool m_active;

	// Points the player has
	int m_points;

	// Max health of the player
	float m_maxHealth;
	// Current health of the player
	float m_currentHealth;

	// Max ammo of the players gun
	int m_maxAmmo;
	// Current ammo of the player gun
	int m_currentAmmo;
	// Reloading progress as percentage for reload bar
	float m_ReloadProgress;
	
	// shield is currently active
	bool m_activeShield = false;
	// Max shield health
	float m_maxShield;
	// Current shield health
	float m_currentShield;
public:
	// Constructor of the HUD
	HUD();

	// HUD currently active
	void SetActive(bool activity);
	// Returns if the HUD is active
	bool IsActive();
	
	// Render the HUD interface
	void Update();

	// Get the current points the player has
	int GetPoints();
	// Give player points
	void GivePoints(int amount);
	// Spend points if player has enough 
	bool SpendPoints(int amount);

	// Set max health of the player
	void SetMaxHealth(float health);
	// Set health of the player
	void SetHealth(float health);
	// Heal player a specific amount
	void Heal(float amount);
	// Fully heal player
	void Heal();
	// Get the max health of the player
	float GetMaxHealth();
	// Get the current health of the player
	float GetCurrentHealth();

	// Set max ammo per clip
	void SetMaxAmmo(int ammo);
	// Set current ammo in the clip
	void SetAmmo(int ammo);
	// Add set amount of bullets to the current
	void Reload(int amount);
	// Full reset ammo back to clip size
	void Reload();
	// Get the max ammo per clip
	int GetMaxAmmo();
	// Get the current ammo in the clip
	int GetCurrentAmmo();
	// Set percentage of reload progress
	void SetReloadProgress(float progress);
	// Get percentage of reload progress
	float GetReloadProgress();

	// Shield currently active
	void SetShield(bool active);
	// Set max shield health
	void SetMaxShield(float amount);
	// Set current shield health
	void SetShield(float amount);
	// Get max shield health
	float GetMaxShield();
	// Get current shield health
	float GetShield();
};