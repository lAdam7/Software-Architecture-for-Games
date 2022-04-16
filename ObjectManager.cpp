#include "ObjectManager.h"

void ObjectManager::AddObject(GameObject* pNewObject)
{
	pObjectList.push_back(pNewObject);
}

void ObjectManager::UpdateAll(double frameTime)
{
	for (auto const& i : pObjectList) {
		i->Update(frameTime);
	}
}

void ObjectManager::RenderAll()
{
	for (auto const& i : pObjectList) {
		i->Render();
	}
}

void ObjectManager::DeleteAll()
{
	for (GameObject* obj : pObjectList)
	{
		delete obj;
		obj = nullptr;
	}
	pObjectList.clear();
}

void ObjectManager::DeleteAllInactive()
{
	for (GameObject*& obj : pObjectList)
	{
		if (!obj->IsActive())
		{
			delete obj;
			obj = nullptr;
		}
	}
	pObjectList.remove(nullptr);
}

void ObjectManager::setCreatingMap(bool creating)
{
	creatingMap = creating;
}

bool ObjectManager::getCreatingMap()
{
	return creatingMap;
}