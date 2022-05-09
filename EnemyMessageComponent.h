#pragma once
#include "MessageComponent.h"

class EnemyMessageComponent : public MessageComponent
{
public:
	void HandleMessage(GameObject* pObject, Message& message) override;
};