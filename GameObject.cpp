#include "GameObject.h"
#include "AnimatedRenderComponent.h"
#include "DoorInputComponent.h"
#include "ObjectManager.h"
#include "PlayerMainInputComponent.h"

// Constructor, create the object assign sent components, sound and type of object. Components can be nullptr
GameObject::GameObject(SoundFX* pSound, InputComponent* pInput, PhysicsComponent* pPhysics, RenderComponent* pRender, CollisionComponent* pCollision, MessageComponent* pMessage, Type type)
{
	pSoundFX = pSound;

	pInputComponent = pInput;
	pPhysicsComponent = pPhysics;
	pRenderComponent = pRender;
	pCollisionComponent = pCollision;
	pMessageComponent = pMessage;
	m_type = type;
};

// Destructor
GameObject::~GameObject()
{
};

// Returns the type of object e.g. WALL, PLAYER, etc
Type GameObject::GetType()
{
	return m_type;
};

// Update the object
void GameObject::Update(HUD* pHUD, float frameTime, bool isFrozen)
{
	if (IsActive()) // Object must be active
	{
		if (pPhysicsComponent && !isFrozen) // not frozen
			pPhysicsComponent->Update(pHUD, this, frameTime);
		if (pRenderComponent)
			pRenderComponent->Update(this);
		if (pInputComponent && !isFrozen) // not frozen
			pInputComponent->Update(pHUD, this, frameTime);
		if (pCollisionComponent && !isFrozen) // not frozen
			pCollisionComponent->Update(pHUD, this, frameTime);
	}
};

// Returns if the object is active
bool GameObject::IsActive() const
{
	return (m_activity == Activity::ACTIVE);
};

// Returns if the object is collidable
bool GameObject::IsCollidable() const
{
	return pCollisionComponent != nullptr;
};

// Returns if the object can be deleted
bool GameObject::CanDelete() const
{
	return (m_activity == Activity::CAN_DELETE);
};

// Activates the object
void GameObject::Activate()
{
	m_activity = Activity::ACTIVE;
};

// Deactivates the object
void GameObject::Deactivate()
{
	m_activity = Activity::INACTIVE;
};

// Delete the object
void GameObject::DeleteObject()
{
	// Components that require additional deletion, to prevent memory leaks
	if (typeid(pRenderComponent) == typeid(AnimatedRenderComponent))
	{
		//AnimatedRenderComponent* pRender = dynamic_cast<AnimatedRenderComponent*>(pRenderComponent);
		//pRender->DeleteObject();
	}
	if (typeid(pInputComponent) == typeid(DoorInputComponent))
	{
		//DoorInputComponent* pDoorInput = dynamic_cast<DoorInputComponent*>(pInputComponent);
		//pDoorInput->DeleteObject();
	}

	PlayerMainInputComponent* pMainInput = dynamic_cast<PlayerMainInputComponent*>(pInputComponent);
	//if (pMainInput)
		//pMainInput->DeleteObject();
	
	if (pInputComponent)
		pInputComponent->DeleteObject();
	if (pPhysicsComponent)
		pPhysicsComponent->DeleteObject();
	if (pRenderComponent)
		pRenderComponent->DeleteObject();
	if (pCollisionComponent)
		pCollisionComponent->DeleteObject();
	
	// Clear all general components
	delete pInputComponent;
	pInputComponent = nullptr;
	delete pPhysicsComponent;
	pPhysicsComponent = nullptr;
	delete pRenderComponent;
	pRenderComponent = nullptr;
	delete pCollisionComponent;
	pCollisionComponent = nullptr;
	delete pMessageComponent;
	pMessageComponent = nullptr;

	// Mark as can be deleted, so object will be removed from list on next exectuin of DeleteAllMarked in ObjectManager
	m_activity = Activity::CAN_DELETE;
};

// Get position of the object
Vector2D GameObject::GetPosition()
{
	return position;
};
// Set position of the object
void GameObject::SetPosition(Vector2D pos)
{
	position = pos;
};

// Get angle of the object
float GameObject::GetAngle()
{
	return angle;
};
// Set angle of the object
void GameObject::SetAngle(float ang)
{
	angle = ang;
};

// Get opacity of the object
float GameObject::GetOpacity()
{
	return opacity;
};
// Set opacity of the object
void GameObject::SetOpacity(float opac)
{
	opacity = opac;
};

// Get scale of the object
float GameObject::GetScale()
{
	return scale;
};
// Set the scale of the object
void GameObject::SetScale(float size)
{
	scale = size;
};

// Get the current SoundFX for the game
SoundFX* GameObject::GetSoundFX()
{
	return pSoundFX;
};

// Get the InputComponent
InputComponent* GameObject::GetInputComponent()
{
	return pInputComponent;
};
// Get the PhysicsComponent
PhysicsComponent* GameObject::GetPhysicsComponent()
{
	return pPhysicsComponent;
};
// Get the RenderComponent
RenderComponent* GameObject::GetRenderComponent()
{
	return pRenderComponent;
};
// Get the CollisionComponent
CollisionComponent* GameObject::GetCollisionComponent()
{
	return pCollisionComponent;
};
// Get the MessageComponent
MessageComponent* GameObject::GetMessageComponent()
{
	return pMessageComponent;
};