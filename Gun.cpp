#include "Gun.h"
#include "gamecode.h"
#include "myinputs.h"
#include "mydrawengine.h"

#include "BulletPhysicsComponent.h"

void Gun::Fire(Vector2D pos, float rotation)
{
	if (CanShoot() && GetBulletDelayCounter() < 0)
	{
		BulletFired();
		ResetBulletDelay();

		GameObject* pBullet = Game::instance.GetObjectManager().Create(L"Bullet");
		Vector2D velocity;
		velocity.setBearing(rotation, 1200.0f);

		Vector2D startingAngle;
		startingAngle.setBearing(rotation + 0.55f, 50.0f);

		pBullet->SetPosition(pos + startingAngle);
		
		BulletPhysicsComponent* pBulletCreated = dynamic_cast<BulletPhysicsComponent*>(pBullet->GetPhysicsComponent());
		pBulletCreated->velocity = velocity;
	}
}

void Gun::Update(HUD* pHUD, float frameTime)
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