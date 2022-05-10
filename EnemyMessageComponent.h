#pragma once
#include "MessageComponent.h"

/*
* Inherits from the MessageComponent for
* sending messages to a enemy
*
* @author W19023403
*/
class EnemyMessageComponent : public MessageComponent
{
public:
	// Overide HandleMessage, to do specific actions on the Enemy if relevent to the object
	void HandleMessage(GameObject* pObject, Message& message) override;
};