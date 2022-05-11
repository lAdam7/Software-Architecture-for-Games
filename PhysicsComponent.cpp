#include "PhysicsComponent.h"

/*
* PhysicsComponent, used mostly for enemy AI aspects
* in this game, and bullet velocity, etc. This class
* is more of a general/misc than directly physics related
* due to it being a small game, always inherited as objects
* will always have different physic components
*
* @author W19023403
*/

// Destructor
PhysicsComponent::~PhysicsComponent()
{
};

// If object requires additional pointers to be removed for deletion of object
void PhysicsComponent::DeleteObject()
{
};