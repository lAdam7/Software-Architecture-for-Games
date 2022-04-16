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
	return active;
}

void GameObject::Deactivate()
{
	active = false;
}