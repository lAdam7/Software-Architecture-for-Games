#include "GameObject.h"

void GameObject::LoadImg(const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);
};

void GameObject::Render()
{
	if (active)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, 1, angle);
	}
};
