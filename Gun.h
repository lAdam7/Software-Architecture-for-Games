#pragma once
#include "vector2D.h"
#include "SoundFX.h"

class Gun
{
private:
	float m_bulletDelay;
	float m_bulletDelayCounter;

	int m_clipSize;
	int m_clipSizeCounter;

	float m_reloadTime;
	float m_reloadTimeCounter;
	bool m_reloading = false;
public:
	void SetBulletDelay(float delay);
	void ResetBulletDelay();
	void DecreaseBulletDelay(float frameTime);

	void SetClipSize(int size);
	void SetClipSizeCounter(int size);
	void ResetClipSize();
	void BulletFired();

	void SetReloadTime(float time);
	void ResetReloadTime();
	void DecreaseReloadTime(float frameTime);

	float GetBulletDelay();
	float GetBulletDelayCounter();

	int GetClipSize();
	int GetClipSizeCounter();

	float GetReloadTime();
	float GetReloadTimeCounter();

	bool CanShoot() const;

	void Update(float frameTime);

	virtual void Fire(Vector2D position, float angle, SoundFX* pSound);
};
