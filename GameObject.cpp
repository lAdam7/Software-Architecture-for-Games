#include "GameObject.h"
#include "AnimatedRenderComponent.h"
#include "DoorInputComponent.h"
#include "ObjectManager.h"

GameObject::GameObject(SoundFX* pSound, InputComponent* pInput, PhysicsComponent* pPhysics, RenderComponent* pRender, CollisionComponent* pCollision, MessageComponent* pMessage, Type type)
{
	pSoundFX = pSound;

	pInputComponent = pInput;
	pPhysicsComponent = pPhysics;
	pRenderComponent = pRender;
	pCollisionComponent = pCollision;
	pMessageComponent = pMessage;
	m_type = type;
}

GameObject::~GameObject()
{

}

Type GameObject::getType()
{
	return m_type;
}

void GameObject::Update(HUD* pHUD, float frameTime, bool isFrozen)
{
	if (IsActive())
	{
		if (pPhysicsComponent && !isFrozen)
			pPhysicsComponent->Update(pHUD, this, frameTime);
		if (pRenderComponent)
			pRenderComponent->Update(this);
		if (pInputComponent && !isFrozen)
			pInputComponent->Update(pHUD, this, frameTime);
		if (pCollisionComponent && !isFrozen)
			pCollisionComponent->Update(pHUD, this, frameTime);
	}
};

bool GameObject::IsActive() const
{
	return (m_activity == Activity::ACTIVE);
}

bool GameObject::IsCollidable() const
{
	return pCollisionComponent != nullptr;
}

bool GameObject::CanDelete() const
{
	return (m_activity == Activity::CAN_DELETE);
}

void GameObject::Activate()
{
	m_activity = Activity::ACTIVE;
}

void GameObject::Deactivate()
{
	m_activity = Activity::INACTIVE;
}

void GameObject::DeleteObject()
{
	if (typeid(pRenderComponent) == typeid(AnimatedRenderComponent))
	{
		AnimatedRenderComponent* animatedRender = dynamic_cast<AnimatedRenderComponent*>(pRenderComponent);
		animatedRender->DeleteObject();
	}
	if (typeid(pInputComponent) == typeid(DoorInputComponent))
	{
		DoorInputComponent* input = dynamic_cast<DoorInputComponent*>(pInputComponent);
		delete input->pPlayer;
		input->pPlayer = nullptr;
	}
	
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

	m_activity = Activity::CAN_DELETE;
}

Vector2D GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(Vector2D pos)
{
	position = pos;
}

float GameObject::GetAngle()
{
	return angle;
}

void GameObject::SetAngle(float ang)
{
	angle = ang;
}

float GameObject::GetOpacity()
{
	return opacity;
}

void GameObject::SetOpacity(float opac)
{
	opacity = opac;
}

float GameObject::GetScale()
{
	return scale;
}

void GameObject::SetScale(float size)
{
	scale = size;
}

bool GameObject::CanReceiveMessages() const
{
	return receiveMessages;
}

void GameObject::ReceiveMessages(bool receive)
{
	receiveMessages = receive;
}

SoundFX* GameObject::GetSoundFX()
{
	return pSoundFX;
}

InputComponent* GameObject::GetInputComponent()
{
	return pInputComponent;
};

PhysicsComponent* GameObject::GetPhysicsComponent()
{
	return pPhysicsComponent;
};

RenderComponent* GameObject::GetRenderComponent()
{
	return pRenderComponent;
};

CollisionComponent* GameObject::GetCollisionComponent()
{
	return pCollisionComponent;
};

MessageComponent* GameObject::GetMessageComponent()
{
	return pMessageComponent;
};