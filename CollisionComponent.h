#pragma once
#include "Shapes.h"
#include "HUD.h"

class GameObject;

enum class ShapeType { CIRCLE, RECTANGLE };
class CollisionComponent
{
private:
	ShapeType type;
	Circle2D circle;
	Rectangle2D rectangle;

	float m_width;
	float m_height;
	float m_radius;
public:
	CollisionComponent(Circle2D shape, float radius);
	CollisionComponent(Rectangle2D shape, float width, float height);
	//CollisionComponent() = default;
	virtual ~CollisionComponent();
	virtual void Update(HUD* pHUD, GameObject* pObject, float frameTime);
	
	virtual IShape2D& GetShape(GameObject* pObject);

	virtual void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject);

	float GetWidth();
	float GetHeight();
	float GetRadius();
};