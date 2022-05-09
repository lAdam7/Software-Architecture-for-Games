#include "ObjectManager.h"
//#include "spaceship.h"
//#include "Bullet.h"
//#include "Asteroid.h"
//#include "Explosion.h"
//#include "Wall.h"
#include "PlayerLegs.h"
#include "PlayerLegsInputComponent.h"
#include "AnimatedRenderComponent.h"
#include "CollisionComponent.h"
#include "PlayerMainInputComponent.h"
#include "BulletPhysicsComponent.h"

#include "EnemyGameObject.h"
#include "EnemyPhysicsComponent.h"

#include "RecurringRenderComponent.h"
#include "ExplosionCollisionComponent.h"
#include "ShieldCollisionComponent.h"
#include "EnemyMessageComponent.h"
#include "BossPhysicsComponent.h"
//#include "Mouse.h"

void ObjectManager::DrawHitbox(IShape2D& shape)
{
	
	if (typeid(shape) == typeid(Circle2D))
	{
		Circle2D circle = dynamic_cast<Circle2D&>(shape);
		MyDrawEngine* mDE = MyDrawEngine::GetInstance();
		
		MyDrawEngine::GetInstance()->FillCircle(circle.GetCentre(), circle.GetRadius(), MyDrawEngine::CYAN);
	}
	else if (typeid(shape) == typeid(Rectangle2D))
	{
		Rectangle2D rectangle = dynamic_cast<Rectangle2D&>(shape);
		MyDrawEngine::GetInstance()->FillRect(rectangle, MyDrawEngine::CYAN);
	}
}

GameObject* ObjectManager::Create(std::wstring name)
{
	GameObject* pNewObject = nullptr;
	if (name == L"Bullet")
	{
		BulletPhysicsComponent* pBulletPhysics = new BulletPhysicsComponent();
		RenderComponent* pBulletRender = new RenderComponent(L"bullet.png");
		CollisionComponent* pBulletCollision = new CollisionComponent(circle, 10.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			pBulletPhysics,
			pBulletRender,
			pBulletCollision,
			nullptr,
			Type::BULLET
		);
	}
	else if (name == L"Wall")
	{
		RenderComponent* pWallRender = new RenderComponent(L"concrete.png");

		CollisionComponent* pWallCollision = new CollisionComponent(rectangle, 256.0f, 256.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pWallRender,
			pWallCollision,
			nullptr,
			Type::WALL
		);
		pNewObject->SetPosition(Vector2D(300, 0));
		pNewObject->Activate();

	}
	else if (name == L"Walls")
	{
		const int WALLCOUNT = 2000;
		RecurringRenderComponent* pRecurringWallRender = new RecurringRenderComponent(L"concrete.png");
		//pRecurringWallRender->SetHorizontal(true);
		//pRecurringWallRender->SetRepeat(WALLCOUNT);
		pRecurringWallRender->SetImageSize(256.0f);

		CollisionComponent* pRecurringWallCollision = new CollisionComponent(rectangle, 256.0f * WALLCOUNT, 256.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pRecurringWallRender,
			pRecurringWallCollision,
			nullptr,
			Type::WALL
		);
		pNewObject->SetPosition(Vector2D(0, -200));
	}
	else if (name == L"PlayerLegs")
	{
		//RenderComponent* pPlayerLegsRender = new RenderComponent(L"idle_0.png");
		RenderComponent* pPlayerLegsRender = new AnimatedRenderComponent();
		
		//pPlayerLegsRender->AddImage(L"survivorRun_0.png");

		PlayerLegsInputComponent* pPlayerLegsInput = new PlayerLegsInputComponent(pPlayerLegsRender);
		CollisionComponent* pCollisionComponent = new CollisionComponent(circle, 50.0f);

		pNewObject = new GameObject(
			pSoundFX,
			pPlayerLegsInput,
			nullptr,
			pPlayerLegsRender,
			pCollisionComponent,
			nullptr,
			Type::PLAYER
		);
		pNewObject->SetAngle(1.5708f*2);
	}
	else if (name == L"PlayerMain")
	{
		RenderComponent* pPlayerMainRender = new AnimatedRenderComponent();
		PlayerMainInputComponent* pPlayerMainInput = new PlayerMainInputComponent(pPlayerMainRender);

		pNewObject = new GameObject(
			pSoundFX,
			pPlayerMainInput,
			nullptr,
			pPlayerMainRender,
			nullptr,
			nullptr,
			Type::IGNOREOBJ
		);
		pNewObject->Activate();
	}
	else if (name == L"Enemy1")
	{
		RenderComponent* pEnemyRender = new AnimatedRenderComponent();
		EnemyPhysicsComponent* pEnemyPhysics = new EnemyPhysicsComponent(pEnemyRender);
	
		CollisionComponent* pCollisionComponent = new CollisionComponent(circle, 50.0f);
		MessageComponent* pEnemyMessage = new EnemyMessageComponent();

		pNewObject = new EnemyGameObject(
			pSoundFX,
			nullptr,
			pEnemyPhysics,
			pEnemyRender,
			pCollisionComponent,
			pEnemyMessage,
			Type::ENEMY
		);
		pNewObject->SetPosition(Vector2D(600, 0));
		pNewObject->Activate();
	}
	else if (name == L"Boss")
	{
		RenderComponent* pEnemyRender = new AnimatedRenderComponent();
		BossPhysicsComponent* pEnemyPhysiscs = new BossPhysicsComponent(pEnemyRender);
		CollisionComponent* pCollisionComponent = new CollisionComponent(circle, 150.0f);

		pNewObject = new EnemyGameObject(
			pSoundFX,
			nullptr,
			pEnemyPhysiscs,
			pEnemyRender,
			pCollisionComponent,
			nullptr,
			Type::ENEMY
		);
		pNewObject->SetPosition(Vector2D(-384, 1788 + 448 + 256 + 704 + 1792 + 512));
	}
	else if (name == L"Shield")
	{
		RenderComponent* pShieldRender = new RenderComponent(L"shield.png");
		CollisionComponent* pShieldCollision = new ShieldCollisionComponent(circle, 140.0f);

		pNewObject = new EnemyGameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pShieldRender,
			pShieldCollision,
			nullptr,
			Type::SHIELD
		);
	}
	else if (name == L"Drop")
	{
		//TODO CLEAN
		RenderComponent* pExplosionRender = new RenderComponent(L"explosive.png");
		CollisionComponent* pExplosionCollision = new CollisionComponent(circle, 30.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pExplosionRender,
			pExplosionCollision,
			nullptr,
			Type::EXPLOSIVE
		);
	}
	else if (name == L"Explosive")
	{
		RenderComponent* pExplosionRender = new RenderComponent(L"explosive.png");
		CollisionComponent* pExplosionCollision = new CollisionComponent(circle, 30.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pExplosionRender,
			pExplosionCollision,
			nullptr,
			Type::EXPLOSIVE
		);
	}
	else if (name == L"Explosion")
	{
		RenderComponent* pExplosionRender = new AnimatedRenderComponent();
		AnimatedRenderComponent* circle = dynamic_cast<AnimatedRenderComponent*>(pExplosionRender);
		
		Circle2D circleV;
		CollisionComponent* pExplosionCollision = new ExplosionCollisionComponent(circleV, 300.0f, 0.3f);

		int explode;
		explode = circle->NewAnimation();
		circle->AddImage(explode, L"explosion1.bmp");
		circle->AddImage(explode, L"explosion2.bmp");
		circle->AddImage(explode, L"explosion3.bmp");
		circle->AddImage(explode, L"explosion4.bmp");
		circle->AddImage(explode, L"explosion5.bmp");
		circle->AddImage(explode, L"explosion6.bmp");
		circle->AddImage(explode, L"explosion7.bmp");
		circle->AddImage(explode, L"explosion8.bmp");

		circle->NextAnimation(explode, explode);
		circle->SetAnimationSpeed(explode, 10.0f);
		circle->SetCurrentAnimation(explode);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pExplosionRender,
			pExplosionCollision,
			nullptr,
			Type::EXPLOSION
		);
	}
	else
	{
		ErrorLogger::Write(L"Could not create item: ");
		ErrorLogger::Writeln(name.c_str());
	}
	if (pNewObject != nullptr)
		m_pObjectList.push_back(pNewObject);

	return pNewObject;
}

void ObjectManager::CreateEnemy(Vector2D pos, GameObject* pTarget, float angle)
{
	GameObject* pEnemy = Create(L"Enemy1");
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pEnemy);
	pEnemyObject->SetTarget(pTarget);
	pEnemyObject->SetPosition(pos);
	pEnemy->SetAngle(angle);
};

void ObjectManager::CreateBoss(GameObject* pTarget)
{
	GameObject* pEnemy = Create(L"Boss");
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pEnemy);
	pEnemyObject->SetTarget(pTarget);
};

void ObjectManager::CreateMultiple(const wchar_t* filename, int repeatX, int repeatY, float imageSize, bool collision, Type type, Vector2D position)
{
	RecurringRenderComponent* pRecurringWallRender = new RecurringRenderComponent(filename);
	pRecurringWallRender->SetRepeatX(repeatX);
	pRecurringWallRender->SetRepeatY(repeatY);
	pRecurringWallRender->SetImageSize(imageSize);

	CollisionComponent* pRecurringWallCollision = nullptr;
	if (collision)
		pRecurringWallCollision = new CollisionComponent(rectangle, imageSize * repeatX, imageSize * repeatY);

	GameObject* pNewObject = new GameObject(
		pSoundFX,
		nullptr,
		nullptr,
		pRecurringWallRender,
		pRecurringWallCollision,
		nullptr,
		type
	);
	pNewObject->SetPosition(position);
	AddObject(pNewObject);
};

void ObjectManager::SetSoundFX(SoundFX* pSound)
{
	pSoundFX = pSound;
}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	if (pNewObject != nullptr)
	{
		m_pObjectList.push_back(pNewObject);
	}
}

void ObjectManager::TransmitMessage(Message msg)
{
	for (GameObject* pNext : m_pObjectList)
	{
		if (pNext && pNext->GetMessageComponent() && pNext->GetMessageComponent()->IsListening())
		{
			pNext->GetMessageComponent()->HandleMessage(pNext, msg);
		}
	}
}




void ObjectManager::UpdateAll(double frameTime, HUD* pHUD)
{
	MyDrawEngine::GetInstance()->WriteInt(50, 50, m_pObjectList.size(), MyDrawEngine::GREEN);

	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = m_pObjectList.begin(); it1 != m_pObjectList.end(); it1++)
	{
		if ((*it1))
		{
			(*it1)->Update(pHUD, (float)frameTime, IsFrozen());
			if ((*it1)->IsCollidable() && !IsFrozen())
			{
				if (SHOWHITBOX)
				{
					DrawHitbox((*it1)->GetCollisionComponent()->GetShape(*it1));
				}
				for (it2 = next(it1); it2 != m_pObjectList.end(); it2++)
				{
					if ((*it2) && (*it2)->IsCollidable())
					{
						if ((*it1) && (*it2) &&
							(*it1)->IsActive() && (*it2)->IsActive() &&
							(*it1)->GetCollisionComponent()->GetShape((*it1)).Intersects((*it2)->GetCollisionComponent()->GetShape((*it2))))
						{
							MyDrawEngine* mDE = MyDrawEngine::GetInstance();
							mDE->WriteText(100, 50, L"Collision detected!", MyDrawEngine::CYAN);

							(*it1)->GetCollisionComponent()->HandleCollision(pHUD, (*it1), (*it2));
							(*it2)->GetCollisionComponent()->HandleCollision(pHUD, (*it2), (*it1));
						}
					}
				}
			}
			
		}
	}
}

void ObjectManager::DeleteAll()
{
	for (GameObject* obj : m_pObjectList)
	{
		obj->DeleteObject();
		delete obj;
		obj = nullptr;
	}
	m_pObjectList.clear();
}

void ObjectManager::DeleteAllInactive()
{
	for (GameObject*& obj : m_pObjectList)
	{
		if (!obj->IsActive())
		{
			obj->DeleteObject();
			delete obj;
			obj = nullptr;
		}
	}
	m_pObjectList.remove(nullptr);
}

void ObjectManager::DeleteAllMarked()
{
	for (GameObject*& obj : m_pObjectList)
	{
		if (obj->CanDelete())
		{
			obj->DeleteObject();
			delete obj;
			obj = nullptr;
		}
	}
	m_pObjectList.remove(nullptr);
}

void ObjectManager::FreezeGame(bool freezeGame)
{
	m_freezeGame = freezeGame;
};
bool ObjectManager::IsFrozen() const
{
	return m_freezeGame;
};

bool ObjectManager::EnemyDirectSight(IShape2D& shape)
{
	for (GameObject* pNext : m_pObjectList)
	{
		if (pNext->getType() == Type::WALL)
		{
			if (pNext && pNext->IsCollidable() && pNext->IsActive() && pNext->GetCollisionComponent()->GetShape(pNext).Intersects(shape))
			{
				return false;
			}
		}
	}
	return true;
};


/*
void ObjectManager::CheckAllCollisions()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = m_pObjectList.begin(); it1 != m_pObjectList.end(); it1++)
	{
		if ((*it1)->IsCollidable())
		{
			if (SHOWHITBOX)
			{
				DrawHitbox((*it1)->GetShape());
			}
				
			for (it2 = next(it1); it2 != m_pObjectList.end(); it2++)
			{
				if ((*it2)->IsCollidable())
				{
					if ((*it1) && (*it2) &&
						(*it1)->IsActive() && (*it2)->IsActive() &&
						(*it1)->GetShape().Intersects((*it2)->GetShape()))
					{
						(*it1)->HandleCollision(**it2);
						(*it2)->HandleCollision(**it1);
					}
				}

			}
		}
	}
}*/