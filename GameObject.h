#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"

class GameObject
{
	private:
		PictureIndex image;
	protected:
		Vector2D position;
		float angle;
		enum Activity { ACTIVE, INACTIVE, CAN_DELETE };
		Activity m_activity;
		void LoadImg(const wchar_t* filename);
	public:
		virtual ~GameObject();
		void Render();
		virtual void Update(double frameTime) = 0;
		bool IsActive() const;
		bool CanDelete() const;
		void Deactivate();
		void DeleteObject();

		virtual void Initialise(Vector2D startingPosition, Vector2D velocity) = 0;
};