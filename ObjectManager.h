#pragma once
#include "GameObject.h"
#include <list>

class ObjectManager
{		
	private:
		std::list<GameObject*> m_pObjectList;
		const bool SHOWHITBOX = true;
		void DrawHitbox(IShape2D& shape);
		void AddObject(GameObject* pNewObject);
	public:
		GameObject* Create(std::wstring name);
		void TransmitMessage(Message msg);

		void UpdateAll(double frameTime);
		void RenderAll();

		void DeleteAll();
		void DeleteAllInactive();
		void DeleteAllMarked();

		void CheckAllCollisions();
};