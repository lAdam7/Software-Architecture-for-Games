#pragma once
#include "GameObject.h"
#include "HUD.h"
#include <list>

class ObjectManager
{		
	private:
		std::list<GameObject*> m_pObjectList;

		SoundFX* pSoundFX;

		const bool SHOWHITBOX = false;
		void DrawHitbox(IShape2D& shape);

		Circle2D circle;
		Rectangle2D rectangle;
	public:
		void AddObject(GameObject* pObject);
		GameObject* Create(std::wstring name);

		void SetSoundFX(SoundFX* pSound);

		void TransmitMessage(Message msg);

		void UpdateAll(double frameTime, HUD* pHUD);

		void DeleteAll();
		void DeleteAllInactive();
		void DeleteAllMarked();

		void CreateMultiple(const wchar_t* filename, int repeatX, int repeatY, float imageSize, bool collision, Type type, Vector2D position);
		void CreateEnemy(Vector2D pos, GameObject* pTarget);
};