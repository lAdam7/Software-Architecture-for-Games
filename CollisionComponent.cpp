#include "CollisionComponent.h"
#include "GameObject.h"
#include "gamecode.h"

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
	/*
	* std::list<GameObject*>::iterator it1;
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
	*/
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
	if (pObject->getType() == Type::BULLET && pCollidedObject->getType() == Type::WALL)
	{
		pObject->Deactivate();
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
