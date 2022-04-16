#pragma once
#include "GameObject.h"
#include <list>

class ObjectManager
{
	private:
		std::list<GameObject*> pObjectList;
		bool creatingMap;
	public:
		void AddObject(GameObject* pNewObject);
		void UpdateAll(double frameTime);
		void RenderAll();
		void DeleteAll();
		void DeleteAllInactive();
		void DeleteAllMarked();
		GameObject* Create(std::wstring name);

		void setCreatingMap(bool creating);
		bool getCreatingMap();
};