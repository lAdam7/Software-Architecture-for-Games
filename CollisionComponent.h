#pragma once
#include "Shapes.h"
#include "HUD.h"

class GameObject;

enum class ShapeType { CIRCLE, RECTANGLE };

/*
* Core CollisionComponent handles of getting
* the shape of every object with collision and
* returnign the correct shape, inherited many times
* for different collision occurances and Updates
*
* @author W19023403
*/
class CollisionComponent
{
private:
	// Type of shape the collision uses
	ShapeType type;

	Circle2D circle;
	Rectangle2D rectangle;

	// Width of the rectangle
	float m_width;
	// Height of the rectangle
	float m_height;
	// Radius of the circle
	float m_radius;
public:
	// Constructor for a circle collision
	CollisionComponent(Circle2D shape, float radius);
	// Constructor for a rectangle collision
	CollisionComponent(Rectangle2D shape, float width, float height);
	// Destructor
	virtual ~CollisionComponent();
	// Updating every frame, overriden in child classes if needed
	virtual void Update(HUD* pHUD, GameObject* pObject, float frameTime);
	
	// Returns the Shape of the collision with the correct positioning and size
	virtual IShape2D& GetShape(GameObject* pObject);

	// Handle a shape colliding with another, overriden in child classes
	virtual void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject);

	// Get the rectangle width
	float GetWidth();
	// Get the rectangle height
	float GetHeight();
	// Get the circle radius
	float GetRadius();

	// If object requires additional pointers to be removed for deletion of object
	virtual void DeleteObject();
};