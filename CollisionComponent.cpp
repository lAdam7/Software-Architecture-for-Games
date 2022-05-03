#include "CollisionComponent.h"
#include "GameObject.h"
#include "gamecode.h"
#include "EnemyGameObject.h"
#include "PlayerLegsInputComponent.h"

CollisionComponent::CollisionComponent(Circle2D shape, float rad)
{
	type = ShapeType::CIRCLE;
	radius = rad;
};

CollisionComponent::CollisionComponent(Rectangle2D shape, float wid, float hei)
{
	type = ShapeType::RECTANGLE;
	width = wid;
	height = hei;
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
		circle.PlaceAt(pObject->GetPosition(), radius);
		return circle;
	}
	else // rectangle
	{
		rectangle.PlaceAt(pObject->GetPosition() + Vector2D(-width/2, -width/2), pObject->GetPosition() + Vector2D(width/2, height/2));
		return rectangle;
	}	
}

void CollisionComponent::HandleCollision(GameObject* pObject, GameObject* pCollidedObject)
{

	if (pObject->getType() == Type::PLAYER && pCollidedObject->getType() == Type::ENEMY)
	{
		PlayerLegsInputComponent* pTest = dynamic_cast<PlayerLegsInputComponent*>(pObject->GetInputComponent());
		pTest->mainCharacter->Deactivate();
		pObject->Deactivate();
	}

	if (pObject->getType() == Type::ENEMY && pCollidedObject->getType() == Type::BULLET)
	{
		GameObject* pEnemyObject = Game::instance.GetObjectManager().Create(L"Enemy1");
		EnemyGameObject* pTest = dynamic_cast<EnemyGameObject*>(pEnemyObject);
		EnemyGameObject* pTestB = dynamic_cast<EnemyGameObject*>(pObject);
		pTest->pTarget = pTestB->pTarget;

		pObject->DeleteObject();
	}
	if (pObject->getType() == Type::BULLET && pCollidedObject->getType() == Type::WALL || pObject->getType() == Type::BULLET && pCollidedObject->getType() == Type::ENEMY)
	{
		pObject->DeleteObject();
	}

	if (pObject->getType() == Type::PLAYER && pCollidedObject->getType() == Type::WALL)
	{	
		Vector2D newPos = pObject->GetPosition();
		// Left
		if (pObject->GetPosition().XValue < pCollidedObject->GetPosition().XValue && pObject->GetPosition().YValue < pCollidedObject->GetPosition().YValue + 130 && pObject->GetPosition().YValue > pCollidedObject->GetPosition().YValue - 130)
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(50, 100, L"L", MyDrawEngine::RED);
			newPos.XValue = pCollidedObject->GetPosition().XValue + (-130 - 50);
		}
		// Right
		if (pObject->GetPosition().XValue > pCollidedObject->GetPosition().XValue && pObject->GetPosition().YValue > pCollidedObject->GetPosition().YValue - 130 && pObject->GetPosition().YValue < pCollidedObject->GetPosition().YValue + 130)
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(100, 100, L"R", MyDrawEngine::RED);
			newPos.XValue = pCollidedObject->GetPosition().XValue + (130 + 50);
		}
		// Top
		if (pObject->GetPosition().YValue > pCollidedObject->GetPosition().YValue && pObject->GetPosition().XValue > pCollidedObject->GetPosition().XValue - 130 && pObject->GetPosition().XValue < pCollidedObject->GetPosition().XValue + 130)
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(150, 100, L"T", MyDrawEngine::RED);
			newPos.YValue = pCollidedObject->GetPosition().YValue + (130 + 50);
		}
		// Bottom
		if (pObject->GetPosition().YValue < pCollidedObject->GetPosition().YValue && pObject->GetPosition().XValue < pCollidedObject->GetPosition().XValue + 130 && pObject->GetPosition().XValue > pCollidedObject->GetPosition().XValue - 130)
		{
			MyDrawEngine* mDE = MyDrawEngine::GetInstance();
			mDE->WriteText(200, 100, L"B", MyDrawEngine::RED);
			newPos.YValue = pCollidedObject->GetPosition().YValue + (-130 - 50);
		}
		pObject->SetPosition(newPos);
	}
};

void CollisionComponent::Update(GameObject* pObject)
{

};
