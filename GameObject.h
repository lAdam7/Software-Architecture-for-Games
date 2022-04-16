#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"

class GameObject
{

	protected:
		Vector2D position;
		float angle;
		bool active;
		void LoadImg(const wchar_t* filename);
	private:
		PictureIndex image;
	public:
		virtual ~GameObject();
		void Render();
		virtual void Update(double frameTime) = 0;
		bool IsActive() const;
		void Deactivate();
};