#include "MessageComponent.h"

/*
* MessageComponent used for components that need
* to listen for events from other objects in the
* game, always used to be inherited from as different
* objects have different responses to messages
*
* @author W19023403
*/

// Constructor listen for events
MessageComponent::MessageComponent()
{
	m_listenForEvents = true;
};

// Listen for events status
void MessageComponent::ListenForEvents(bool listen)
{
	m_listenForEvents = listen;
};

// Currently listening for events
bool MessageComponent::IsListening() const
{
	return m_listenForEvents;
};