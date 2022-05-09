#include "MessageComponent.h"

MessageComponent::MessageComponent()
{
	m_listenForEvents = true;
};

void MessageComponent::ListenForEvents(bool listen)
{
	m_listenForEvents = listen;
};

bool MessageComponent::IsListening() const
{
	return m_listenForEvents;
};