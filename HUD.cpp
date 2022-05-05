#include "HUD.h"
#include <string>

HUD::HUD()
{
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


		pDE->WriteText(topRightPosition + Vector2D(-300, -600), L"Health: 100", MyDrawEngine::WHITE);
		Rectangle2D rectHealth;
		rectHealth.PlaceAt(topRightPosition + Vector2D(-300, -665), topRightPosition + Vector2D(0, -645));
		pDE->FillRect(rectHealth, MyDrawEngine::GREEN);


		std::wstring strAmmo = L"Ammo: " + std::to_wstring(m_currentAmmo);
		pDE->WriteText(topRightPosition + Vector2D(-300, -690), strAmmo.c_str(), MyDrawEngine::WHITE);
		Rectangle2D rectAmmo;
		rectAmmo.PlaceAt(topRightPosition + Vector2D(-300 + GetReloadProgress(), -755), topRightPosition + Vector2D(0, -735));
		pDE->FillRect(rectAmmo, MyDrawEngine::CYAN);

		
		/*
		pDE->WriteText(topRightPosition + Vector2D(-300, -780), L"Shield: 100", MyDrawEngine::WHITE);
		Rectangle2D rectShield;
		rectShield.PlaceAt(topRightPosition + Vector2D(-300, -845), topRightPosition + Vector2D(0, -825));
		pDE->FillRect(rectShield, MyDrawEngine::RED);
		*/
	};
}

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