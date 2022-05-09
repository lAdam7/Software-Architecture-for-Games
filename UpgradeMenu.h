#pragma once
#include "HUD.h"

class UpgradeMenu 
{
private:
	bool m_active;
	bool m_opening;
	static const int HEALTHUPGRADES = 3;
	const int m_healthUpgradesHealth[HEALTHUPGRADES] = { 150, 200, 250 };
	const int m_healthUpgradesPoints[HEALTHUPGRADES] = { 100, 250, 400 };
	static const int SHIELDUPGRADES = 3;
	const int m_shieldUpgradesShield[SHIELDUPGRADES] = { 150, 200, 250 };
	const int m_shieldUpgradesPoints[SHIELDUPGRADES] = { 50, 100, 125 };
public:
	void Update(float frameTime, HUD* pHUD);
	int m_currentHealthLevel = -1;
	int m_currentShieldLevel = -1;
	int m_selectedOption = 0;
};