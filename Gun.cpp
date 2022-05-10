#include "Gun.h"
#include "gamecode.h"
#include "myinputs.h"
#include "mydrawengine.h"

#include "BulletPhysicsComponent.h"
#include "AnimatedRenderComponent.h"

bool Gun::Fire(Vector2D pos, float rotation, GameObject* pObject, int reload)
{
	if (CanShoot() && GetBulletDelayCounter() < 0)
	{
		if (!m_activeSpeedBoost)
		{
			BulletFired();
		}
		
		ResetBulletDelay();

		GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
		Vector2D velocity;
		velocity.setBearing(rotation, (m_activeSpeedBoost) ? 1400.0f : 950.0f);

		Vector2D startingAngle;
		startingAngle.setBearing(rotation + 0.55f, 50.0f);

		pBullet->SetPosition(pos + startingAngle);
		
		BulletPhysicsComponent* pBulletCreated = dynamic_cast<BulletPhysicsComponent*>(pBullet->GetPhysicsComponent());
		pBulletCreated->velocity = velocity;

		if (m_activeShotgunBoost)
		{
			GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity2;
			velocity2.setBearing(rotation + 0.05f, (m_activeSpeedBoost) ? 1400.0f : 950.0f);
			pBullet->SetPosition(pos + startingAngle);

			BulletPhysicsComponent* pBulletCreated = dynamic_cast<BulletPhysicsComponent*>(pBullet->GetPhysicsComponent());
			pBulletCreated->velocity = velocity2;

			GameObject* pBullet3 = Game::instance.GetObjectManager().Create(L"Bullet");
			Vector2D velocity3;
			velocity3.setBearing(rotation - 0.05f, (m_activeSpeedBoost) ? 1400.0f : 950.0f);
			pBullet3->SetPosition(pos + startingAngle);

			BulletPhysicsComponent* pBulletCreated3 = dynamic_cast<BulletPhysicsComponent*>(pBullet3->GetPhysicsComponent());
			pBulletCreated3->velocity = velocity3;
		}

		if (!CanShoot()) // start reload animation
		{
			return true;
		}

		Message msg;
		msg.type = EventType::BULLET_FIRED;
		msg.pSource = pBullet;
		Game::instance.GetObjectManager().TransmitMessage(msg);
	}
	return false;
}

bool Gun::Update(HUD* pHUD, float frameTime)
{
	if (CanShoot())
	{
		DecreaseBulletDelay(frameTime);

		MyInputs* pInputs = MyInputs::GetInstance();
		pInputs->SampleKeyboard();

		if (pInputs->KeyPressed(DIK_R) && GetClipSize() != GetClipSizeCounter())
		{
			SetClipSizeCounter(0);
			return true;
		}
	} 
	else
	{
		if (m_reloadTimeCounter == m_reloadTime)
		{
			Message msg;
			msg.type = EventType::CHARACTER_IS_RELOADING;
			Game::instance.GetObjectManager().TransmitMessage(msg);
		}
		DecreaseReloadTime(frameTime);
	}
	
	if (m_activeSpeedBoost)
	{
		m_speedBoostTimer += frameTime;
		if (m_speedBoostTimer > SPEEDBOOSTLENGTH)
		{
			m_activeSpeedBoost = false;
		}
	}
	if (m_activeShotgunBoost)
	{
		m_shotgunBoostTimer += frameTime;
		if (m_shotgunBoostTimer > SHOTGUNBOOSTLENGTH)
		{
			m_activeShotgunBoost = false;
		}
	}

	MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	Vector2D topRightPosition = mDE->GetViewport().GetTopRight();
	Vector2D ammoPosition = Vector2D(topRightPosition.XValue - 100, topRightPosition.YValue - 300);

	float percentage = (CanShoot())
		? (100 - ((GetClipSizeCounter() / (float)GetClipSize()) * 100)) * 3
		: (( GetReloadTimeCounter() / GetReloadTime() ) * 100) * 3;

	pHUD->SetReloadProgress(percentage);

	Rectangle2D rectangle;
	rectangle.PlaceAt(ammoPosition + Vector2D(-150 + percentage, -60), ammoPosition + Vector2D(50, -45));
	//mDE->FillRect(rectangle, MyDrawEngine::CYAN, 0.0f);
	
	//mDE->WriteInt(ammoPosition, GetClipSizeCounter(), MyDrawEngine::CYAN);
	return false;
}

void Gun::SetBulletDelay(float delay)
{
	m_bulletDelay = delay;
	ResetBulletDelay();
}

void Gun::ResetBulletDelay()
{
	m_bulletDelayCounter = m_bulletDelay;
}

void Gun::DecreaseBulletDelay(float frameTime)
{
	m_bulletDelayCounter = m_bulletDelayCounter - frameTime;
}

void Gun::SetClipSize(int size)
{
	m_clipSize = size;
	ResetClipSize();
}

void Gun::SetClipSizeCounter(int size)
{
	m_clipSizeCounter = size;
}

void Gun::ResetClipSize()
{
	m_clipSizeCounter = m_clipSize;
}

void Gun::BulletFired()
{
	m_clipSizeCounter = m_clipSizeCounter - 1;
}

void Gun::SetReloadTime(float time)
{
	m_reloadTime = time;
	ResetReloadTime();
}

void Gun::ResetReloadTime()
{
	m_reloadTimeCounter = m_reloadTime;
}

void Gun::DecreaseReloadTime(float frameTime)
{
	m_reloadTimeCounter = m_reloadTimeCounter - frameTime;
	if (m_reloadTimeCounter < 0)
	{
		ResetClipSize();
		ResetReloadTime();
	}
}

float Gun::GetBulletDelay()
{
	return m_bulletDelay;
}

float Gun::GetBulletDelayCounter()
{
	return m_bulletDelayCounter;
}

int Gun::GetClipSize()
{
	return m_clipSize;
}

int Gun::GetClipSizeCounter()
{
	return m_clipSizeCounter;
}

float Gun::GetReloadTime()
{
	return m_reloadTime;
}

float Gun::GetReloadTimeCounter()
{
	return m_reloadTimeCounter;
}

bool Gun::CanShoot() const
{
	return (m_clipSizeCounter > 0);
}

void Gun::StartSpeedBoost()
{
	m_activeSpeedBoost = true;
	m_speedBoostTimer = 0.0f;
}

void Gun::StartShotgunBoost()
{
	m_activeShotgunBoost = true;
	m_shotgunBoostTimer = 0.0f;
}