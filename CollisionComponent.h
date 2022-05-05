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
public:
	CollisionComponent(Circle2D shape, float radius);
	CollisionComponent(Rectangle2D shape, float width, float height);
	virtual ~CollisionComponent();
	virtual void Update(GameObject* pObject);
	
	virtual IShape2D& GetShape(GameObject* pObject);

	virtual void HandleCollision(HUD* pHUD, GameObject* pObject, GameObject* pCollidedObject); // = 0 TODO

	float radius;
	float width;
	float height;
};