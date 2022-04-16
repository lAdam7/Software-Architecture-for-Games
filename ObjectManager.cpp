#include "ObjectManager.h"
#include "spaceship.h"
#include "Bullet.h"
#include "Asteroid.h"

void ObjectManager::AddObject(GameObject* pNewObject)
{
	if (pNewObject != nullptr)
	{
		pObjectList.push_back(pNewObject);
	}
}

GameObject* ObjectManager::Create(std::wstring name)
{
	GameObject* pNewObject = nullptr;
	if (name == L"Bullet")
	{
		pNewObject = new Bullet();
	}
	else if (name == L"Spaceship")
	{
		pNewObject = new Spaceship();
	}
	else if (name == L"Asteroid")
	{
		pNewObject = new Asteroid();
	}
	else
	{
		ErrorLogger::Write(L"Could not create item: ");
		ErrorLogger::Writeln(name.c_str());
	}
	AddObject(pNewObject);

	return pNewObject;
}

void ObjectManager::UpdateAll(double frameTime)
{
	for (auto const& i : pObjectList) {
		i->Update(frameTime);
	}
}

void ObjectManager::RenderAll()
{
	MyDrawEngine::GetInstance()->WriteInt(50, 50, pObjectList.size(), MyDrawEngine::GREEN);
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

void ObjectManager::DeleteAllMarked()
{
	for (GameObject*& obj : pObjectList)
	{
		if (obj->CanDelete())
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