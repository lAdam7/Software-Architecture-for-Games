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
};

void CollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
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

// If object requires additional pointers to be removed for deletion of object
void CollisionComponent::DeleteObject()
{
};