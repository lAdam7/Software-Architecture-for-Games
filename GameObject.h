#pragma once
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "MessageComponent.h"
#include "mydrawengine.h"
#include "SoundFX.h"
#include "Message.h"

struct Message;
enum class Activity { ACTIVE, INACTIVE, CAN_DELETE };
enum class Type { IGNOREOBJ, PLAYER, ENEMY, WALL, BULLET, SHIELD, KEY, DOOR, EXPLOSIVE, EXPLOSION };

class GameObject
{
	private:
		SoundFX* pSoundFX;

		InputComponent* pInputComponent;
		PhysicsComponent* pPhysicsComponent;
		RenderComponent* pRenderComponent;
		CollisionComponent* pCollisionComponent;
		MessageComponent* pMessageComponent;
		Type m_type;

		Activity m_activity;
		
		Vector2D position;
		float angle;
		float opacity;
		float scale;

		bool collidable;
		bool receiveMessages;
	protected:
		void ReceiveMessages(bool receive);
	public:
		GameObject(SoundFX* pSoundFX, InputComponent* pInput, PhysicsComponent* pPhysics, RenderComponent* pRender, CollisionComponent* pCollision, MessageComponent* pMessage, Type type);
		virtual ~GameObject();

		Type getType();

		bool IsCollidable() const;

		float GetAngle();
		void SetAngle(float angle);

		float GetScale();
		void SetScale(float scale);

		float GetOpacity();
		void SetOpacity(float opacity);

		Vector2D GetPosition();
		void SetPosition(Vector2D position);

		bool CanReceiveMessages() const;

		bool IsActive() const;
		bool CanDelete() const;
		void Activate();
		void Deactivate();
		void DeleteObject();	

		void Update(HUD* pHUD, float frameTime, bool isFrozen);

		SoundFX* GetSoundFX();

		InputComponent* GetInputComponent();
		PhysicsComponent* GetPhysicsComponent();
		RenderComponent* GetRenderComponent();
		CollisionComponent* GetCollisionComponent();
		MessageComponent* GetMessageComponent();
};
