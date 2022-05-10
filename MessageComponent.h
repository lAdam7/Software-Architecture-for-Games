#pragma once
#include "Message.h"

class GameObject;

/*
* MessageComponent used for components that need
* to listen for events from other objects in the
* game, always used to be inherited from as different
* objects have different responses to messages
*
* @author W19023403
*/
class MessageComponent
{
private:
	// Listening for messages
	bool m_listenForEvents;
public:
	// Constructor set to listening for messages by default
	MessageComponent();
	
	// Set if listening for events / messages
	void ListenForEvents(bool listen);
	// Currently listening for events/matches
	bool IsListening() const;

	// What to do with the message / handle
	virtual void HandleMessage(GameObject* pObject, Message& message) = 0;
};