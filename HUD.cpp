#include "HUD.h"
#include <string>

HUD::HUD()
{
	m_maxHealth = 100;
	m_currentHealth = 100;

	m_points = 0;
	SetActive(true);
}

void HUD::Update()
{
	if (IsActive())
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		Vector2D topRightPosition = pDE->GetViewport().GetTopRight();

		std::wstring strPoints = L"Points: " + std::to_wstring(GetPoints());
		pDE->WriteText(topRightPosition + Vector2D(-300, -500), strPoints.c_str(), MyDrawEngine::WHITE);


		float percentage = 300 - (((GetCurrentHealth() / GetMaxHealth() * 100)) * 3);

		std::wstring strHealth = L"Health: " + std::to_wstring((int)GetCurrentHealth()) + L" / " + std::to_wstring((int)GetMaxHealth());
		pDE->WriteText(topRightPosition + Vector2D(-300, -600), strHealth.c_str(), MyDrawEngine::WHITE);
		Rectangle2D rectHealth;
		rectHealth.PlaceAt(topRightPosition + Vector2D(-300 + percentage, -665), topRightPosition + Vector2D(0, -645));
		pDE->FillRect(rectHealth, MyDrawEngine::GREEN);


		std::wstring strAmmo = L"Ammo: " + std::to_wstring(m_currentAmmo);
		pDE->WriteText(topRightPosition + Vector2D(-300, -690), strAmmo.c_str(), MyDrawEngine::WHITE);
		Rectangle2D rectAmmo;
		rectAmmo.PlaceAt(topRightPosition + Vector2D(-300 + GetReloadProgress(), -755), topRightPosition + Vector2D(0, -735));
		pDE->FillRect(rectAmmo, MyDrawEngine::CYAN);

		if (m_activeShield)
		{
			float percentage = 300 - (((m_currentShield / m_maxShield * 100)) * 3);
			std::wstring strShield = L"Shield: " + std::to_wstring((int)m_currentShield) + L" / " + std::to_wstring((int)m_maxShield);
			pDE->WriteText(topRightPosition + Vector2D(-300, -780), strShield.c_str(), MyDrawEngine::WHITE);
			Rectangle2D rectShield;
			rectShield.PlaceAt(topRightPosition + Vector2D(-300 + percentage, -845), topRightPosition + Vector2D(0, -825));
			pDE->FillRect(rectShield, MyDrawEngine::RED);
		}
	};
}

void HUD::SetShield(bool active)
{
	m_activeShield = active;
	m_currentShield = m_maxShield;
};

void HUD::SetActive(bool activity)
{
	m_active = activity;
};
bool HUD::IsActive()
{
	return m_active;
};

int HUD::GetPoints()
{
	return m_points;
};
void HUD::GivePoints(int amount)
{
	m_points += amount;
};
bool HUD::SpendPoints(int amount)
{
	if (GetPoints() >= amount)
	{
		m_points = m_points - amount;
		return true;
	}
	return false;
};

void HUD::SetMaxHealth(float health)
{
	m_maxHealth = health;
};
void HUD::SetHealth(float health)
{
	m_currentHealth = health;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
};
void HUD::Heal(float amount)
{
	m_currentHealth += amount;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
};
void HUD::Heal()
{
	m_currentHealth = m_maxHealth;
};
float HUD::GetMaxHealth()
{
	return m_maxHealth;
};
float HUD::GetCurrentHealth()
{
	return m_currentHealth;
}

void HUD::SetMaxAmmo(int ammo)
{
	m_maxAmmo = ammo;
};
void HUD::SetAmmo(int ammo)
{
	m_currentAmmo = ammo;
	if (m_currentAmmo > m_maxAmmo)
		m_currentAmmo = m_maxAmmo;
};
void HUD::Reload(int amount)
{
	m_currentAmmo += amount;
	if (m_currentAmmo > m_maxAmmo)
		m_currentAmmo = m_maxAmmo;
};
void HUD::Reload()
{
	m_currentAmmo = m_maxAmmo;
};
int HUD::GetMaxAmmo()
{
	return m_maxAmmo;
};
int HUD::GetCurrentAmmo()
{
	return m_currentAmmo;
};
void HUD::SetReloadProgress(float progress)
{
	m_ReloadProgress = progress;
};
float HUD::GetReloadProgress()
{
	return m_ReloadProgress;
};

void HUD::SetMaxShield(float amount)
{
	m_maxShield = amount;
	m_currentShield = amount;
};
void HUD::SetShield(float amount)
{
	m_currentShield = amount;
};
float HUD::GetMaxShield()
{
	return m_maxShield;
};
float HUD::GetShield()
{
	return m_currentShield;
};