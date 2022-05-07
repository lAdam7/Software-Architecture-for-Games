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
		RenderComponent* pBulletRender = new RenderComponent(L"bullet.bmp");
		CollisionComponent* pBulletCollision = new CollisionComponent(circle, 10.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			pBulletPhysics,
			pBulletRender,
			pBulletCollision,
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
			Type::WALL
		);
		pNewObject->SetPosition(Vector2D(300, 0));
		pNewObject->Activate();

	}
	else if (name == L"Walls")
	{
		const int WALLCOUNT = 1000;
		RecurringRenderComponent* pRecurringWallRender = new RecurringRenderComponent();
		pRecurringWallRender->SetHorizontal(true);
		pRecurringWallRender->SetRepeat(WALLCOUNT);
		pRecurringWallRender->SetImageSize(256.0f);

		CollisionComponent* pRecurringWallCollision = new CollisionComponent(rectangle, 256.0f * WALLCOUNT, 256.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pRecurringWallRender,
			pRecurringWallCollision,
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
			Type::PLAYER
		);
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
			Type::IGNOREOBJ
		);
		pNewObject->Activate();
	}
	else if (name == L"Enemy1")
	{
		RenderComponent* pEnemyRender = new AnimatedRenderComponent();
		EnemyPhysicsComponent* pEnemyPhysics = new EnemyPhysicsComponent(pEnemyRender);
		CollisionComponent* pCollisionComponent = new CollisionComponent(circle, 50.0f);

		pNewObject = new EnemyGameObject(
			pSoundFX,
			nullptr,
			pEnemyPhysics,
			pEnemyRender,
			pCollisionComponent,
			Type::ENEMY
		);
		pNewObject->SetPosition(Vector2D(600, 0));
		pNewObject->Activate();
	}
	else if (name == L"Shield")
	{
		RenderComponent* pShieldRender = new RenderComponent(L"shield.png");
		CollisionComponent* pShieldCollision = new CollisionComponent(circle, 120.0f);

		pNewObject = new EnemyGameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pShieldRender,
			pShieldCollision,
			Type::SHIELD
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
		//if (pNext && pNext->CanReceiveMessages())
		{
		//	//pNext->HandleMessage(msg);
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
			(*it1)->Update(pHUD, frameTime);
			if ((*it1)->IsCollidable())
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