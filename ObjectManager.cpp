#include "ObjectManager.h"
#include "spaceship.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Wall.h"
#include "Feet.h"
#include "Mouse.h"

void ObjectManager::DrawHitbox(IShape2D& shape)
{
	if (typeid(shape) == typeid(Circle2D))
	{
		Circle2D circle = dynamic_cast<Circle2D&>(shape);
		MyDrawEngine::GetInstance()->FillCircle(circle.GetCentre(), circle.GetRadius(), MyDrawEngine::CYAN);
	}
	else if (typeid(shape) == typeid(Rectangle2D))
	{
		Rectangle2D rectangle = dynamic_cast<Rectangle2D&>(shape);
		MyDrawEngine::GetInstance()->FillRect(rectangle, MyDrawEngine::CYAN);
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
	else if (name == L"Explosion")
	{
		pNewObject = new Explosion();
	}
	else if (name == L"Wall")
	{
		pNewObject = new Wall();
	}
	else if (name == L"Feet")
	{
		pNewObject = new Feet();
	}
	else if (name == L"Mouse")
	{
		pNewObject = new Mouse();
	}
	else
	{
		ErrorLogger::Write(L"Could not create item: ");
		ErrorLogger::Writeln(name.c_str());
	}
	AddObject(pNewObject);

	return pNewObject;
}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	if (pNewObject != nullptr)
	{
		m_pObjectList.push_back(pNewObject);
	}
}

void ObjectManager::TransmitMessage(Message msg)
{
	for (GameObject* pNext : m_pObjectList)
	{
		if (pNext && pNext->CanReceiveMessages())
		{
			pNext->HandleMessage(msg);
		}
	}
}




void ObjectManager::UpdateAll(double frameTime)
{
	for (auto const& i : m_pObjectList) {
		i->Update(frameTime);
	}
}

void ObjectManager::RenderAll(double frameTime)
{
	MyDrawEngine::GetInstance()->WriteInt(50, 50, m_pObjectList.size(), MyDrawEngine::GREEN);
	for (auto const& i : m_pObjectList) {
		i->Render();
		i->Update(frameTime);
	}
}




void ObjectManager::DeleteAll()
{
	for (GameObject* obj : m_pObjectList)
	{
		delete obj;
		obj = nullptr;
	}
	m_pObjectList.clear();
}

void ObjectManager::DeleteAllInactive()
{
	for (GameObject*& obj : m_pObjectList)
	{
		if (!obj->IsActive())
		{
			delete obj;
			obj = nullptr;
		}
	}
	m_pObjectList.remove(nullptr);
}

void ObjectManager::DeleteAllMarked()
{
	for (GameObject*& obj : m_pObjectList)
	{
		if (obj->CanDelete())
		{
			delete obj;
			obj = nullptr;
		}
	}
	m_pObjectList.remove(nullptr);
}




void ObjectManager::CheckAllCollisions()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = m_pObjectList.begin(); it1 != m_pObjectList.end(); it1++)
	{
		if ((*it1)->IsCollidable())
		{
			if (SHOWHITBOX)
			{
				DrawHitbox((*it1)->GetShape());
			}
				
			for (it2 = next(it1); it2 != m_pObjectList.end(); it2++)
			{
				if ((*it2)->IsCollidable())
				{
					if ((*it1) && (*it2) &&
						(*it1)->IsActive() && (*it2)->IsActive() &&
						(*it1)->GetShape().Intersects((*it2)->GetShape()))
					{
						(*it1)->HandleCollision(**it2);
						(*it2)->HandleCollision(**it1);
					}
				}

			}
		}
	}
}