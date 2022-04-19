#pragma once

class GameObject;

enum class EventType { CHARACTER_DIED, OBJECT_DESTROYED, EXPLOSION, BULLET_FIRED };
struct Message
{
	EventType type;
	Vector2D location;
	GameObject* pSource;
};