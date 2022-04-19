#pragma once
#include "GameObject.h"
#include <list>

class ObjectManager
{		
	private:
		std::list<GameObject*> pObjectList;
		const bool ShowHitbox = false;
		void DrawHitbox(IShape2D& shape);
	public:
		GameObject* Create(std::wstring name);
		void AddObject(GameObject* pNewObject);
		void TransmitMessage(Message msg);

		void UpdateAll(double frameTime);
		void RenderAll();

		void DeleteAll();
		void DeleteAllInactive();
		void DeleteAllMarked();

		void CheckAllCollisions();
};