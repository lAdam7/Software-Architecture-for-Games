#include "Gun.h"
#include "gamecode.h"
#include "myinputs.h"



#include "mydrawengine.h"

void Gun::Fire(Vector2D pos, float rotation, SoundFX* pSoundFX)
{
	if (CanShoot() && GetBulletDelayCounter() < 0)
	{
		BulletFired();
		ResetBulletDelay();

		GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
		Vector2D velocity;
		velocity.setBearing(rotation, 10.0f);

		Vector2D startingAngle;
		startingAngle.setBearing(rotation + 0.55f, 50.0f);

		pBullet->Initialise(pos + startingAngle, velocity, pSoundFX);
	}
}

void Gun::Update(float frameTime)
{
	if (CanShoot())
	{
		DecreaseBulletDelay(frameTime);

		MyInputs* pInputs = MyInputs::GetInstance();
		pInputs->SampleKeyboard();

		if (pInputs->KeyPressed(DIK_R) && GetClipSize() != GetClipSizeCounter())
		{
			SetClipSizeCounter(0);
		}
	} 
	else
	{
		DecreaseReloadTime(frameTime);
	}
	
	MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	mDE->WriteInt(Vector2D(50, 50), GetClipSizeCounter(), MyDrawEngine::CYAN);
}

void Gun::SetBulletDelay(float delay)
{
	bulletDelay = delay;
	ResetBulletDelay();
}

void Gun::ResetBulletDelay()
{
	bulletDelayCounter = bulletDelay;
}

void Gun::DecreaseBulletDelay(float frameTime)
{
	bulletDelayCounter = bulletDelayCounter - frameTime;
}

void Gun::SetClipSize(int size)
{
	clipSize = size;
	ResetClipSize();
}

void Gun::SetClipSizeCounter(int size)
{
	clipSizeCounter = size;
}

void Gun::ResetClipSize()
{
	clipSizeCounter = clipSize;
}

void Gun::BulletFired()
{
	clipSizeCounter = clipSizeCounter - 1;
}

void Gun::SetReloadTime(float time)
{
	reloadTime = time;
	ResetReloadTime();
}

void Gun::ResetReloadTime()
{
	reloadTimeCounter = reloadTime;
}

void Gun::DecreaseReloadTime(float frameTime)
{
	reloadTimeCounter = reloadTimeCounter - frameTime;
	if (reloadTimeCounter < 0)
	{
		ResetClipSize();
		ResetReloadTime();
	}
}

float Gun::GetBulletDelay()
{
	return bulletDelay;
}

float Gun::GetBulletDelayCounter()
{
	return bulletDelayCounter;
}

int Gun::GetClipSize()
{
	return clipSize;
}

int Gun::GetClipSizeCounter()
{
	return clipSizeCounter;
}

float Gun::GetReloadTime()
{
	return reloadTime;
}

float Gun::GetReloadTimeCounter()
{
	return reloadTimeCounter;
}

bool Gun::CanShoot() const
{
	return (clipSizeCounter > 0);
}