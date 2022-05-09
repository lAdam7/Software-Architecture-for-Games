#pragma once
#include "vector2D.h"

class GameObject;

enum class EventType { CHARACTER_DIED, EXPLOSION, BULLET_FIRED, CHARACTER_IS_RELOADING };
struct Message
{
	EventType type;
	Vector2D location;
	GameObject* pSource;
};