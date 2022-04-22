#pragma once
#include "mydrawengine.h"
#include "SoundFX.h"
#include "Message.h"

struct Message;
enum class Activity { ACTIVE, INACTIVE, CAN_DELETE };

class GameObject
{
	private:
		PictureIndex image;
		Activity m_activity;
		
		float angle;
		float opacity;
		float scale;
		bool collidable;
		bool receiveMessages;
	protected:
		Vector2D position; // TODO move private
		
		void SetPosition(Vector2D position);
		void SetOpacity(float opacity);
		void SetScale(float scale);
		

		void ReceiveMessages(bool receive);

		void LoadImg(const wchar_t* filename);
	public:
		GameObject();
		virtual ~GameObject();

		void CanCollide(bool collide);
		void SetAngle(float angle);
		virtual void Initialise(Vector2D startingPosition, Vector2D velocity, SoundFX* pSoundFX) = 0;
		virtual IShape2D& GetShape() = 0;

		virtual void HandleCollision(GameObject& other) = 0;

		virtual void HandleMessage(Message& msg) = 0;

		void Render();
		virtual void Update(double frameTime) = 0;

		bool IsActive() const;
		bool CanDelete() const;
		void Activate();
		void Deactivate();
		void DeleteObject();

		Vector2D GetPosition();
		float GetAngle();
		float GetOpacity();
		float GetScale();

		bool IsCollidable() const;

		bool CanReceiveMessages() const;
};
