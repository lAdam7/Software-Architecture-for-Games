#pragma once
#include "mydrawengine.h"
#include "SoundFX.h"
#include "Message.h"

struct Message;

class GameObject
{
	private:
		PictureIndex image;
	protected:
		bool collidable;
		Vector2D position;
		float angle;
		float opacity;
		float scale;
		enum class Activity { ACTIVE, INACTIVE, CAN_DELETE };
		Activity m_activity;
		void LoadImg(const wchar_t* filename);
		bool receiveMessages;
	public:
		GameObject();
		virtual ~GameObject();
		void Render();
		virtual void Update(double frameTime) = 0;
		bool IsActive() const;
		bool CanDelete() const;
		void Activate();
		void Deactivate();
		void DeleteObject();
		bool IsCollidable() const;

		Vector2D GetPosition();
		float GetAngle();
		void ReceiveMessages(bool receive);
		bool CanReceiveMessages();

		virtual void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX) = 0;
		virtual IShape2D& GetShape() = 0;

		virtual void HandleCollision(GameObject& other) = 0;

		virtual void HandleMessage(Message& msg) = 0;
};
