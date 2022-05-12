#pragma once
#include "vector2D.h"

class GameObject;

enum class EventType { CHARACTER_DIED, EXPLOSION, BULLET_FIRED, CHARACTER_IS_RELOADING };

/*
* Sending a message to other objects, 
* sends the type of event, location the event 
* occured if needed and the pointer to the
* object the event originated from
*
* @author W19023403
*/
struct Message
{
	EventType type;
	Vector2D location;
	GameObject* pSource;
};