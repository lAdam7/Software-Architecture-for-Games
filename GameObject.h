#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "SoundFX.h"

class GameObject
{
	private:
		PictureIndex image;
	protected:
		bool collidable;
		Vector2D position;
		float angle;
		enum class Activity { ACTIVE, INACTIVE, CAN_DELETE };
		Activity m_activity;
		void LoadImg(const wchar_t* filename);
	public:
		virtual ~GameObject();
		void Render();
		virtual void Update(double frameTime) = 0;
		bool IsActive() const;
		bool CanDelete() const;
		void Activate();
		void Deactivate();
		void DeleteObject();
		bool IsCollidable() const;

		virtual void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX) = 0;
		virtual IShape2D& GetShape() = 0;

		virtual void HandleCollision(GameObject& other) = 0;
};