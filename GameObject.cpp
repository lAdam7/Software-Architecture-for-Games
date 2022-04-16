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
		pDE->DrawAt(position, image, 1, angle);
	}
};

bool GameObject::IsActive() const
{
	return (m_activity == Activity::ACTIVE);
}

bool GameObject::CanDelete() const
{
	return (m_activity == Activity::CAN_DELETE);
}

void GameObject::Deactivate()
{
	m_activity = INACTIVE;
}

void GameObject::DeleteObject()
{
	m_activity = CAN_DELETE;
}