#include "Gun.h"
#include "gamecode.h"
#include "myinputs.h"
#include "mydrawengine.h"
#include "BulletPhysicsComponent.h"
#include "AnimatedRenderComponent.h"

/*
* Gun class for controlling the players gun,
* handling bullet delays, clip size, reload time,
* and the boosts from the power drops
*
* @author W19023403
*/

// Fire a bullet
bool Gun::Fire(Vector2D pos, float rotation, GameObject* pObject, int reload)
{
	if (CanShoot() && GetBulletDelayCounter() < 0) // Got enough bullets, and enough time has passed since the last bullet being fired
	{
		if (!m_activeSpeedBoost) // No boost active for infinite bullet, so decrease clip by 1
		{
			BulletFired();
		}
		ResetBulletDelay(); // Reset to start timing again

		GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
		Vector2D velocity;
		velocity.setBearing(rotation, (m_activeSpeedBoost) ? 1400.0f : 950.0f); // Direction player is facing to shoot the bullet velocity

		Vector2D startingAngle;
		startingAngle.setBearing(rotation + 0.55f, 50.0f); // Bullet fires closer to the playermodels gun

		BulletPhysicsComponent* pBulletCreated = dynamic_cast<BulletPhysicsComponent*>(pBullet->GetPhysicsComponent());
		pBullet->SetPosition(pos + startingAngle); // Set position to the bullet
		pBulletCreated->SetVelocity(velocity); // Set the velocity to the bullet

		Game::instance.GetObjectManager().GetSoundFX()->PlayShot();

		if (m_activeShotgunBoost) // Shotgun active, repeat above for 2 more bullets 2 be fired in slightly different angles
		{
			GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity2;
			velocity2.setBearing(rotation + 0.05f, (m_activeSpeedBoost) ? 1400.0f : 950.0f);
			pBullet->SetPosition(pos + startingAngle);

			BulletPhysicsComponent* pBulletCreated = dynamic_cast<BulletPhysicsComponent*>(pBullet->GetPhysicsComponent());
			pBulletCreated->SetVelocity(velocity2);

			GameObject* pBullet3 = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity3;
			velocity3.setBearing(rotation - 0.05f, (m_activeSpeedBoost) ? 1400.0f : 950.0f);
			pBullet3->SetPosition(pos + startingAngle);

			BulletPhysicsComponent* pBulletCreated3 = dynamic_cast<BulletPhysicsComponent*>(pBullet3->GetPhysicsComponent());
			pBulletCreated3->SetVelocity(velocity3);
		}

		if (!CanShoot()) // Can't shoot
		{
			return true;
		}

		// Message for enemies to listen for, to check if bullet will hit them
		Message msg;
		msg.type = EventType::BULLET_FIRED;
		msg.pSource = pBullet;
		Game::instance.GetObjectManager().TransmitMessage(msg);
	}
	return false;
};

// Update the gun called evey frame from the player
bool Gun::Update(HUD* pHUD, float frameTime)
{
	if (CanShoot()) // Player could shoot
	{
		DecreaseBulletDelay(frameTime); // Decrease time since last bullet fired

		MyInputs* pInputs = MyInputs::GetInstance();
		pInputs->SampleKeyboard();

		// Player is pressed R to reload and not a fresh clip in the gun
		if (pInputs->KeyPressed(DIK_R) && GetClipSize() != GetClipSizeCounter())
		{
			SetClipSizeCounter(0);
			return true;
		}
	}
	else // Can't shoot
	{
		if (m_reloadTimeCounter == m_reloadTime) // Start of reloading process
		{
			// Message for enemeies, to rush the player as they're reloading
			Message msg;
			msg.type = EventType::CHARACTER_IS_RELOADING;
			Game::instance.GetObjectManager().TransmitMessage(msg);
		}
		DecreaseReloadTime(frameTime); // Decrease reload time
	}

	// Faster bullets / infinite bullets still active, decrease time
	if (m_activeSpeedBoost)
	{
		m_speedBoostTimer += frameTime;
		if (m_speedBoostTimer > SPEEDBOOSTLENGTH) // powerup finished, disable
		{
			m_activeSpeedBoost = false;
		}
	}
	// Shotgun bullets powerup still active
	if (m_activeShotgunBoost)
	{
		m_shotgunBoostTimer += frameTime;
		if (m_shotgunBoostTimer > SHOTGUNBOOSTLENGTH) // powerup finished, disable
		{
			m_activeShotgunBoost = false;
		}
	}

	// Percentage of reload process
	float percentage = (CanShoot())
		? (100 - ((GetClipSizeCounter() / (float)GetClipSize()) * 100)) * 3
		: ((GetReloadTimeCounter() / GetReloadTime()) * 100) * 3;

	// Set reload process to the HUD to show
	pHUD->SetReloadProgress(percentage);

	return false;
};

// The bullet delay to firing between bullets
void Gun::SetBulletDelay(float delay)
{
	m_bulletDelay = delay;
	ResetBulletDelay();
};
// Reset the bullet delay counter to the total time to decrease time
void Gun::ResetBulletDelay()
{
	m_bulletDelayCounter = m_bulletDelay;
};
// Decrease bullet delays once < 0 the player can fire again
void Gun::DecreaseBulletDelay(float frameTime)
{
	m_bulletDelayCounter = m_bulletDelayCounter - frameTime;
};

// Set the size of the clip
void Gun::SetClipSize(int size)
{
	m_clipSize = size;
	ResetClipSize();
};
// Set size of the bullets left in the clip
void Gun::SetClipSizeCounter(int size)
{
	m_clipSizeCounter = size;
};
// Reload finished, ResetClipSize back to the total clip size
void Gun::ResetClipSize()
{
	m_clipSizeCounter = m_clipSize;
};

// Bullet has been fired, decrease the amount of bullets in the clip
void Gun::BulletFired()
{
	m_clipSizeCounter = m_clipSizeCounter - 1;
};

// Set the time required for a reload
void Gun::SetReloadTime(float time)
{
	m_reloadTime = time;
	ResetReloadTime();
};
// Reset the timer for reloading
void Gun::ResetReloadTime()
{
	m_reloadTimeCounter = m_reloadTime;
};
// Decrease reload timer
void Gun::DecreaseReloadTime(float frameTime)
{
	m_reloadTimeCounter = m_reloadTimeCounter - frameTime;
	if (m_reloadTimeCounter < 0) // reload finished, reset the clip size and the reload time
	{
		ResetClipSize();
		ResetReloadTime();
	}
};
// Returns the bullet delay between shots
float Gun::GetBulletDelay()
{
	return m_bulletDelay;
};
// Returns the current bullet delay between the last bullet
float Gun::GetBulletDelayCounter()
{
	return m_bulletDelayCounter;
};

// Returns the clip size
int Gun::GetClipSize()
{
	return m_clipSize;
};
// Returns the current amount of bullets in the clip
int Gun::GetClipSizeCounter()
{
	return m_clipSizeCounter;
};

// Returns the time required for a reload
float Gun::GetReloadTime()
{
	return m_reloadTime;
};

// Returns the current time passed, in the active reload
float Gun::GetReloadTimeCounter()
{
	return m_reloadTimeCounter;
};

// Can the player currently shoot, have enough bullets in the clip
bool Gun::CanShoot() const
{
	return (m_clipSizeCounter > 0);
};

// Start a speed/infine boost, called from the Drop picked up
void Gun::StartSpeedBoost()
{
	m_activeSpeedBoost = true;
	m_speedBoostTimer = 0.0f;
};
// Start a shotgun boost effect, called from the Drop picked up
void Gun::StartShotgunBoost()
{
	m_activeShotgunBoost = true;
	m_shotgunBoostTimer = 0.0f;
};