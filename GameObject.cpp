#include "GameObject.h"
#include "AnimatedRenderComponent.h"
#include "ObjectManager.h"

GameObject::GameObject(SoundFX* pSound, InputComponent* pInput, PhysicsComponent* pPhysics, RenderComponent* pRender, CollisionComponent* pCollision, Type type)
{
	pSoundFX = pSound;

	pInputComponent = pInput;
	pPhysicsComponent = pPhysics;
	pRenderComponent = pRender;
	pCollisionComponent = pCollision;
	m_type = type;
}

GameObject::~GameObject()
{

}

Type GameObject::getType()
{
	return m_type;
}

void GameObject::Update(double frameTime)
{
	if (IsActive())
	{
		if (pPhysicsComponent)
			pPhysicsComponent->Update(this);
		if (pRenderComponent)
			pRenderComponent->Update(this);
		if (pInputComponent)
			pInputComponent->Update(this, frameTime);
		if (pCollisionComponent)
			pCollisionComponent->Update(this);
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
	
	delete pInputComponent;
	pInputComponent = nullptr;
	delete pPhysicsComponent;
	pPhysicsComponent = nullptr;
	delete pRenderComponent;
	pRenderComponent = nullptr;
	delete pCollisionComponent;
	pCollisionComponent = nullptr;

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