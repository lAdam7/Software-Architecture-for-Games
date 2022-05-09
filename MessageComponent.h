#pragma once
#include "Message.h"

class GameObject;

class MessageComponent
{
private:
	bool m_listenForEvents;
public:
	MessageComponent();
	void ListenForEvents(bool listen);
	bool IsListening() const;
	virtual void HandleMessage(GameObject* pObject, Message& message) = 0;
};