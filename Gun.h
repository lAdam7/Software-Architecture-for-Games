#pragma once
#include "vector2D.h"
#include "HUD.h"
#include "GameObject.h"

/*
* Gun class for controlling the players gun,
* handling bullet delays, clip size, reload time,
* and the boosts from the power drops
*
* @author W19023403
*/
class Gun
{
private:
	// Bullet delay
	float m_bulletDelay;
	// Counting towards the bullet delay
	float m_bulletDelayCounter;
	
	// The size of the clip
	int m_clipSize;
	// The current amount of bullets left in the clip
	int m_clipSizeCounter;

	// The time required for reloading
	float m_reloadTime;
	// The current timer passed during reloading
	float m_reloadTimeCounter;
	// Currently reloading
	bool m_reloading;

	// Time the speed boost lasts
	float const SPEEDBOOSTLENGTH = 8.0f;
	// Boost currently active
	bool m_activeSpeedBoost;
	// Current time passed, since given boost
	float m_speedBoostTimer;

	// Time the shotgun boost lasts
	float const SHOTGUNBOOSTLENGTH = 8.0f;
	// Boost currently active
	bool m_activeShotgunBoost;
	// Current time passed, since given boost
	float m_shotgunBoostTimer;
public:
	// Set the bullet delay between bullets
	void SetBulletDelay(float delay);
	// Reset bullet delay back to 0, ready for next bullet to be fired
	void ResetBulletDelay();
	// Decrease timer since last bullet fired
	void DecreaseBulletDelay(float frameTime);

	// Set the amount of bullets that can go in a clip
	void SetClipSize(int size);
	// Set the current amount of bullets left in clip
	void SetClipSizeCounter(int size);
	// Reset the clip size
	void ResetClipSize();
	// Bullet fired decrease the amount in the clip
	void BulletFired();

	// Set the time required to reload
	void SetReloadTime(float time);
	// Reset the timer for reloading
	void ResetReloadTime();
	// Decrease the reload timer
	void DecreaseReloadTime(float frameTime);

	// Get the bullet delay
	float GetBulletDelay();
	// Get the current bullet delay counter
	float GetBulletDelayCounter();

	// Get the max clip size
	int GetClipSize();
	// Get the current bullets in the clip
	int GetClipSizeCounter();

	// Get the time required for reload
	float GetReloadTime();
	// Get how much time has passed, during ongoing reload
	float GetReloadTimeCounter();

	// Can the player shoot, enough bullets to fire
	bool CanShoot() const;

	// Check all the timers, update reload progress if needed
	bool Update(HUD* pHUD, float frameTime);

	// Fire a bullet, if got enough bullets, etc
	virtual bool Fire(Vector2D position, float angle, GameObject* pObject, int reload);

	// Start a speed/infinite ammo boost
	void StartSpeedBoost();
	// Start the shotgun boost
	void StartShotgunBoost();
};
