#include "CollisionComponent.h"
#include "GameObject.h"
#include "gamecode.h"
#include "EnemyGameObject.h"
#include "PlayerLegsInputComponent.h"
#include "BulletPhysicsComponent.h"
#include <corecrt_math_defines.h>

#include "EnemyPhysicsComponent.h"
#include "KeyInputComponent.h"
#include "DoorInputComponent.h"
#include "ShieldCollisionComponent.h"

CollisionComponent::CollisionComponent(Circle2D shape, float rad)
{
	type = ShapeType::CIRCLE;
	m_radius = rad;
};

CollisionComponent::CollisionComponent(Rectangle2D shape, float width, float height)
{
	type = ShapeType::RECTANGLE;
	m_width = width;
	m_height = height;
};

CollisionComponent::~CollisionComponent()
{
};

IShape2D& CollisionComponent::GetShape(GameObject* pObject)
{
	//MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	//mDE->FillCircle(pObject->GetPosition(), radius, MyDrawEngine::RED);
	if (type == ShapeType::CIRCLE) 
	{
		circle.PlaceAt(pObject->GetPosition(), m_radius);
		return circle;
	}
	else // rectangle
	{
		rectangle.PlaceAt(pObject->GetPosition() + Vector2D(-m_width/2, -m_height/2), pObject->GetPosition() + Vector2D(m_width/2, m_height/2));
		return rectangle;
	}	
}

void CollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
	if (pObject->getType() == Type::SHIELD && pCollidedObject->getType() == Type::ENEMY)
	{
		ShieldCollisionComponent* pTest = dynamic_cast<ShieldCollisionComponent*>(pObject->GetCollisionComponent());
		pTest->Damage(1);
	}
	if (pObject->getType() == Type::ENEMY && pCollidedObject->getType() == Type::EXPLOSION)
	{
		EnemyGameObject* pTest = dynamic_cast<EnemyGameObject*>(pObject);
		pTest->Damage(2);
	}
	if (pObject->getType() == Type::EXPLOSIVE && pCollidedObject->getType() == Type::BULLET)
	{
		GameObject* pExplosion = Game::instance.GetObjectManager().Create(L"Explosion");
		pExplosion->SetPosition(pObject->GetPosition());

		pObject->DeleteObject();
	}
	if (pObject->getType() == Type::KEY && pCollidedObject->getType() == Type::PLAYER)
	{
		KeyInputComponent* pKeyInput = dynamic_cast<KeyInputComponent*>(pObject->GetInputComponent());
		DoorInputComponent* pDoorInput = dynamic_cast<DoorInputComponent*>(pKeyInput->GetDoor()->GetInputComponent());
		pDoorInput->PickedKey();
		pObject->DeleteObject();
	}

	if (pObject->getType() == Type::ENEMY && pCollidedObject->getType() == Type::ENEMY || pObject->getType() == Type::ENEMY && pCollidedObject->getType() == Type::SHIELD || pObject->getType() == Type::ENEMY && pCollidedObject->getType() == Type::PLAYER)
	{
		float dx = pCollidedObject->GetPosition().XValue - pObject->GetPosition().XValue;
		float dy = pCollidedObject->GetPosition().YValue - pObject->GetPosition().YValue;

		float dist = sqrt(dx * dx + dy * dy);

		float nx = dx / dist;
		float ny = dy / dist;

		float touchDistFromB1 = (dist * (m_radius / (m_radius + pCollidedObject->GetCollisionComponent()->m_radius)));
		float contactX = pObject->GetPosition().XValue + nx * touchDistFromB1;
		float contactY = pObject->GetPosition().YValue + ny * touchDistFromB1;

		pObject->SetPosition(Vector2D(contactX - nx * m_radius, contactY - ny * m_radius));
	}

	if (pObject->getType() == Type::PLAYER && pCollidedObject->getType() == Type::ENEMY)
	{
		//EnemyGameObject* pGO = dynamic_cast<EnemyGameObject*>(pCollidedObject);
		//EnemyPhysicsComponent* pTest = dynamic_cast<EnemyPhysicsComponent*>(pGO->GetPhysicsComponent());
		
		//PlayerLegsInputComponent* pTest = dynamic_cast<PlayerLegsInputComponent*>(pObject->GetInputComponent());
		//pTest->mainCharacter->Deactivate();
		//pObject->Deactivate();
	}

	if (pObject->getType() == Type::ENEMY && pCollidedObject->getType() == Type::BULLET)
	{
		/*
		GameObject* pEnemyObject = Game::instance.GetObjectManager().Create(L"Enemy1");
		EnemyGameObject* pTest = dynamic_cast<EnemyGameObject*>(pEnemyObject);
		EnemyGameObject* pTestB = dynamic_cast<EnemyGameObject*>(pObject);
		pTest->SetTarget(pTestB->GetTarget());

		pObject->DeleteObject();*/

		EnemyGameObject* pTest = dynamic_cast<EnemyGameObject*>(pObject);
		pTest->Damage(100);
	}
	if (pObject->getType() == Type::BULLET && pCollidedObject->getType() == Type::WALL)
	{
		pObject->DeleteObject();
		/*
		BulletPhysicsComponent* pTest = dynamic_cast<BulletPhysicsComponent*>(pObject->GetPhysicsComponent());

		Vector2D normal = (pObject->GetPosition() - pCollidedObject->GetPosition()).unitVector();
		if (normal * pTest->velocity < 0)
		{
			pTest->velocity = pTest->velocity - 2 * (pTest->velocity * normal) * normal;
			pTest->velocity = 0.5f * pTest->velocity;
		}*/
	}

	if (pObject->getType() == Type::BULLET && pCollidedObject->getType() == Type::ENEMY)
	{
		pHUD->GivePoints(50);
		pObject->DeleteObject();
	}

	if (/*pObject->getType() == Type::PLAYER && pCollidedObject->getType() == Type::WALL ||*/ pObject->getType() == Type::ENEMY && pCollidedObject->getType() == Type::WALL)
	{	
		const float COLLIDEDWIDTH = pCollidedObject->GetCollisionComponent()->GetWidth();
		const float COLLIDEDHEIGHT = pCollidedObject->GetCollisionComponent()->GetHeight();

		Vector2D newPos = pObject->GetPosition();
		// Left
		if (pObject->GetPosition().XValue < pCollidedObject->GetPosition().XValue && pObject->GetPosition().YValue < pCollidedObject->GetPosition().YValue + (COLLIDEDHEIGHT * 0.5) && pObject->GetPosition().YValue > pCollidedObject->GetPosition().YValue - (COLLIDEDHEIGHT * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(50, 100, L"L", MyDrawEngine::RED);
			newPos.XValue = (float)(pCollidedObject->GetPosition().XValue - ((COLLIDEDWIDTH * 0.5) + 50));
		}
		// Right
		if (pObject->GetPosition().XValue > pCollidedObject->GetPosition().XValue && pObject->GetPosition().YValue > pCollidedObject->GetPosition().YValue - (COLLIDEDHEIGHT * 0.5) && pObject->GetPosition().YValue < pCollidedObject->GetPosition().YValue + (COLLIDEDHEIGHT * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(100, 100, L"R", MyDrawEngine::RED);
			newPos.XValue = (float)(pCollidedObject->GetPosition().XValue + ((COLLIDEDWIDTH * 0.5) + 50));
		}
		// Top
		if (pObject->GetPosition().YValue > pCollidedObject->GetPosition().YValue && pObject->GetPosition().XValue > pCollidedObject->GetPosition().XValue - (COLLIDEDWIDTH * 0.5) && pObject->GetPosition().XValue < pCollidedObject->GetPosition().XValue + (COLLIDEDWIDTH * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(150, 100, L"T", MyDrawEngine::RED);
			newPos.YValue = (float)(pCollidedObject->GetPosition().YValue + ((COLLIDEDHEIGHT * 0.5) + 50));
		}
		// Bottom
		if (pObject->GetPosition().YValue < pCollidedObject->GetPosition().YValue && pObject->GetPosition().XValue < pCollidedObject->GetPosition().XValue + (COLLIDEDWIDTH * 0.5) && pObject->GetPosition().XValue > pCollidedObject->GetPosition().XValue - (COLLIDEDWIDTH * 0.5))
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(200, 100, L"B", MyDrawEngine::RED);
			newPos.YValue = (float)(pCollidedObject->GetPosition().YValue - ((COLLIDEDHEIGHT * 0.5) + 50));
		}
		pObject->SetPosition(newPos);
	}
};

void CollisionComponent::Update(GameObject* pObject, float frameTime)
{

};

float CollisionComponent::GetHeight()
{
	return m_height;
};

float CollisionComponent::GetWidth()
{
	return m_width;
};

float CollisionComponent::GetRadius()
{
	return m_radius;
};