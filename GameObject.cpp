#include "GameObject.h"

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

float GameObject::GetAngle()
{
	return angle;
}