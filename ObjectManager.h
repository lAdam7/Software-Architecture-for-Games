#pragma once
#include "GameObject.h"
#include <list>

class ObjectManager
{
	private:
		std::list<GameObject*> pObjectList;
		bool creatingMap;
		const bool ShowHitbox = true;
		void DrawHitbox(IShape2D& shape);
	public:
		void AddObject(GameObject* pNewObject);
		void UpdateAll(double frameTime);
		void RenderAll();
		void DeleteAll();
		void DeleteAllInactive();
		void DeleteAllMarked();
		void CheckAllCollisions();
		GameObject* Create(std::wstring name);;
		void TransmitMessage(Message msg);
};