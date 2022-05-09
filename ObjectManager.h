#pragma once
#include "GameObject.h"
#include "HUD.h"
#include <list>

enum class Type_Freeze { PAUSE, WON, DEFEAT, BUY };
class ObjectManager
{		
	private:
		std::list<GameObject*> m_pObjectList;

		SoundFX* pSoundFX;

		const bool SHOWHITBOX = false;
		void DrawHitbox(IShape2D& shape);

		Circle2D circle;
		Rectangle2D rectangle;
		
		bool m_freezeGame;
		Type_Freeze m_freezeScreen;
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
		void CreateEnemy(Vector2D pos, GameObject* pTarget, float angle);
		void CreateBoss(GameObject* pTarget);

		void FreezeGame(bool freeze, Type_Freeze m_freezeScreen);
		void FreezeGame(bool freeze);
		bool IsFrozen() const;
		Type_Freeze GetFreezeScreen();


		bool EnemyDirectSight(IShape2D& shape);

};