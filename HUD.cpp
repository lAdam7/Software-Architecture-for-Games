#include "HUD.h"
#include <string>
#include "mydrawengine.h"

/*
* Main HUD for the player, shows the users
* current points, alongside the health status,
* ammo status and the active shield if active
*
* @author W19023403
*/

// Constructor set default values, prepared for later potential upgrades
HUD::HUD()
{
	m_maxHealth = 100;
	m_currentHealth = 100;

	m_maxShield = 100.0f;

	m_points = 0;
	SetActive(true); // display the HUD
};

// Update the HUD called every frame
void HUD::Update()
{
	if (IsActive()) // Active / can render
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		Vector2D topRightPosition = pDE->GetViewport().GetTopRight();

		std::wstring strPoints = L"Points: " + std::to_wstring(GetPoints());
		pDE->WriteText(topRightPosition + Vector2D(-300, -500), strPoints.c_str(), MyDrawEngine::WHITE); // Current points


		float percentage = 300 - (((GetCurrentHealth() / GetMaxHealth() * 100)) * 3); // health percentage

		std::wstring strHealth = L"Health: " + std::to_wstring((int)GetCurrentHealth()) + L" / " + std::to_wstring((int)GetMaxHealth());
		pDE->WriteText(topRightPosition + Vector2D(-300, -600), strHealth.c_str(), MyDrawEngine::WHITE); // Current health
		Rectangle2D rectHealth;
		rectHealth.PlaceAt(topRightPosition + Vector2D(-300 + percentage, -665), topRightPosition + Vector2D(0, -645)); // Health bar
		pDE->FillRect(rectHealth, MyDrawEngine::GREEN);


		std::wstring strAmmo = L"Ammo: " + std::to_wstring(m_currentAmmo);
		pDE->WriteText(topRightPosition + Vector2D(-300, -690), strAmmo.c_str(), MyDrawEngine::WHITE); // Current ammo
		Rectangle2D rectAmmo;
		rectAmmo.PlaceAt(topRightPosition + Vector2D(-300 + GetReloadProgress(), -755), topRightPosition + Vector2D(0, -735)); // Ammo bar
		pDE->FillRect(rectAmmo, MyDrawEngine::CYAN);

		if (m_activeShield) // Shield is currenlt active
		{
			float percentage = 300 - (((m_currentShield / m_maxShield * 100)) * 3); // shield percentage

			std::wstring strShield = L"Shield: " + std::to_wstring((int)m_currentShield) + L" / " + std::to_wstring((int)m_maxShield);
			pDE->WriteText(topRightPosition + Vector2D(-300, -780), strShield.c_str(), MyDrawEngine::WHITE); // Current shield status
			Rectangle2D rectShield;
			rectShield.PlaceAt(topRightPosition + Vector2D(-300 + percentage, -845), topRightPosition + Vector2D(0, -825)); // Shield bar
			pDE->FillRect(rectShield, MyDrawEngine::RED);
		}
	}
};

// To render the HUD or not
void HUD::SetActive(bool activity)
{
	m_active = activity;
};
// HUD is currently active
bool HUD::IsActive()
{
	return m_active;
};

// Get the players current points
int HUD::GetPoints()
{
	return m_points;
};
// Give the player n points
void HUD::GivePoints(int amount)
{
	m_points += amount;
};
// Take n points from the player if they have enough, returns boolean on success
bool HUD::SpendPoints(int amount)
{
	if (GetPoints() >= amount)
	{
		m_points = m_points - amount;
		return true;
	}
	return false;
};

// Max health of the player
void HUD::SetMaxHealth(float health)
{
	m_maxHealth = health;
};
// Current health of the player
void HUD::SetHealth(float health)
{
	m_currentHealth = health;
	if (m_currentHealth > m_maxHealth) // higher than tha max, bring down
		m_currentHealth = m_maxHealth;
};
// Heal player n amount
void HUD::Heal(float amount)
{
	m_currentHealth += amount;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
};
// Fully heal player
void HUD::Heal()
{
	m_currentHealth = m_maxHealth;
};
// Get the max health
float HUD::GetMaxHealth()
{
	return m_maxHealth;
};
// Get the current health
float HUD::GetCurrentHealth()
{
	return m_currentHealth;
}

// Set max ammo per clip
void HUD::SetMaxAmmo(int ammo)
{
	m_maxAmmo = ammo;
};
// Current ammo in clip
void HUD::SetAmmo(int ammo)
{
	m_currentAmmo = ammo;
	if (m_currentAmmo > m_maxAmmo)
		m_currentAmmo = m_maxAmmo;
};
// Add n amounts to the ammo
void HUD::Reload(int amount)
{
	m_currentAmmo += amount;
	if (m_currentAmmo > m_maxAmmo)
		m_currentAmmo = m_maxAmmo;
};
// Reset to clip size
void HUD::Reload()
{
	m_currentAmmo = m_maxAmmo;
};
// Get the max ammo
int HUD::GetMaxAmmo()
{
	return m_maxAmmo;
};
// Get current ammo in clip
int HUD::GetCurrentAmmo()
{
	return m_currentAmmo;
};
// Set the reload progress
void HUD::SetReloadProgress(float progress)
{
	m_ReloadProgress = progress;
};
// Get the reload progress
float HUD::GetReloadProgress()
{
	return m_ReloadProgress;
};

// Set the shield to be displayed in UI on screen
void HUD::SetShield(bool active)
{
	m_activeShield = active;
	m_currentShield = m_maxShield;
};
// Set the max shield health
void HUD::SetMaxShield(float amount)
{
	m_maxShield = amount;
	m_currentShield = amount;
};
// Set current health of shield
void HUD::SetShield(float amount)
{
	m_currentShield = amount;
};
// Get max health of shield
float HUD::GetMaxShield()
{
	return m_maxShield;
};
// Get current health of shield
float HUD::GetShield()
{
	return m_currentShield;
};