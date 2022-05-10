#pragma once
#include "HUD.h"

/*
* Pressing B whilst in game, opens up
* the shop to upgrade health and shields
* if user has enough points
*
* @author W19023403
*/
class UpgradeMenu 
{
private:
	// Health upgrades
	static const int HEALTHUPGRADES = 3;
	const int m_healthUpgradesHealth[HEALTHUPGRADES] = { 150, 200, 250 }; // Different healths for levels
	const int m_healthUpgradesPoints[HEALTHUPGRADES] = { 100, 250, 400 }; // Points cost for different health levels

	// Shield upgrades
	static const int SHIELDUPGRADES = 3;
	const int m_shieldUpgradesShield[SHIELDUPGRADES] = { 150, 200, 250 }; // Different shield for levels
	const int m_shieldUpgradesPoints[SHIELDUPGRADES] = { 50, 100, 125 }; // Points cost for different shield levels

	// User current health level
	int m_currentHealthLevel = -1;
	// User current shield level
	int m_currentShieldLevel = -1;
	// Navigation option selected
	int m_selectedOption = 0;
public:
	// Render menu onto the screen
	void Update(float frameTime, HUD* pHUD);
};