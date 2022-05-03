#pragma once
#include "GameObject.h"
#include <list>

class ObjectManager
{		
	private:
		std::list<GameObject*> m_pObjectList;

		SoundFX* pSoundFX;

		const bool SHOWHITBOX = false;
		void DrawHitbox(IShape2D& shape);

		void AddObject(GameObject* pNewObject);

		Circle2D circle;
		Rectangle2D rectangle;
	public:
		GameObject* Create(std::wstring name);

		void SetSoundFX(SoundFX* pSound);

		void TransmitMessage(Message msg);

		void UpdateAll(double frameTime);

		void DeleteAll();
		void DeleteAllInactive();
		void DeleteAllMarked();
};