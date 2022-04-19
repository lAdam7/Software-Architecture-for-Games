#pragma once
#include "vector2D.h"
#include "SoundFX.h"

class Gun
{
private:
	float bulletDelay;
	float bulletDelayCounter;

	int clipSize;
	int clipSizeCounter;

	float reloadTime;
	float reloadTimeCounter;
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
