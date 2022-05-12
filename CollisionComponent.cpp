#include "CollisionComponent.h"
#include "GameObject.h"
#include "gamecode.h"

/*
* Core CollisionComponent handles of getting
* the shape of every object with collision and
* returnign the correct shape, inherited many times
* for different collision occurances and Updates
*
* @author W19023403
*/

// Constructor for a circle collision
CollisionComponent::CollisionComponent(Circle2D shape, float rad)
{
	type = ShapeType::CIRCLE;
	m_radius = rad;
};
// Constructor for a rectangle collision
CollisionComponent::CollisionComponent(Rectangle2D shape, float width, float height)
{
	type = ShapeType::RECTANGLE;
	m_width = width;
	m_height = height;
};
// Destructor
CollisionComponent::~CollisionComponent()
{
};

// Get the shape that the obused uses, with the correct size and postion
IShape2D& CollisionComponent::GetShape(GameObject* pObject)
{
	if (type == ShapeType::CIRCLE)
	{
		circle.PlaceAt(pObject->GetPosition(), m_radius);
		return circle;
	}
	else // rectangle
	{
		rectangle.PlaceAt(pObject->GetPosition() + Vector2D(-m_width / 2, -m_height / 2), pObject->GetPosition() + Vector2D(m_width / 2, m_height / 2));
		return rectangle;
	}
};

// Handle a shape colliding with another, overriden in child classes
void CollisionComponent::HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject)
{
};
// Updating every frame, overriden in child classes if needed
void CollisionComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{

};

// Get the rectangle height
float CollisionComponent::GetHeight()
{
	return m_height;
};
// Get the rectangle width
float CollisionComponent::GetWidth()
{
	return m_width;
};

// Get the circle radius
float CollisionComponent::GetRadius()
{
	return m_radius;
};

// If object requires additional pointers to be removed for deletion of object
void CollisionComponent::DeleteObject()
{
};