#include "GameObject.h"

GameObject::GameObject()
{
	scale = 1;
	receiveMessages = false;
}

GameObject::~GameObject()
{

}

void GameObject::LoadImg(const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);
};

void GameObject::Render()
{
	if (IsActive())
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, scale, angle, opacity);
	}
};

bool GameObject::IsActive() const
{
	return (m_activity == Activity::ACTIVE);
}

bool GameObject::IsCollidable() const
{
	return collidable;
}

void GameObject::CanCollide(bool collide)
{
	collidable = collide;
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