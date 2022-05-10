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
enum class Activity { ACTIVE, INACTIVE, CAN_DELETE }; // Object state
enum class Type { IGNOREOBJ, PLAYER, ENEMY, WALL, BULLET, SHIELD, KEY, DOOR, EXPLOSIVE, EXPLOSION, ENEMY_BOSS, POWERUP }; // Object types
/*
* The object, stored the input, physics, render, collision, messsage
* and type of the object that is created they can be null, stores
* common info like position and angle
*
* @author W19023403
*/
class GameObject
{
private:
	SoundFX* pSoundFX;

	InputComponent* pInputComponent;
	PhysicsComponent* pPhysicsComponent;
	RenderComponent* pRenderComponent;
	CollisionComponent* pCollisionComponent;
	MessageComponent* pMessageComponent;

	Type m_type; // Type of object
	Activity m_activity; // State of object
		
	Vector2D position;
	float angle;
	float opacity;
	float scale = 1.0f; // Not frequently used predefine
public:
	// Constructor, creating the object
	GameObject(SoundFX* pSoundFX,
		InputComponent* pInput, 
		PhysicsComponent* pPhysics, 
		RenderComponent* pRender, 
		CollisionComponent* pCollision, 
		MessageComponent* pMessage, 
		Type type
	);
	// Destructor
	virtual ~GameObject(); 

	// Returns the type of object e.g. PLAYER, WALL, etc
	Type GetType();

	// Return if the object has a collision component
	bool IsCollidable() const;

	// Angle of object
	float GetAngle();

	// Set angle of object
	void SetAngle(float angle); 

	// Scale of object
	float GetScale(); 
	// Set scale of object
	void SetScale(float scale);

	// Opacity of object
	float GetOpacity(); 
	// Set opacity of object
	void SetOpacity(float opacity);

	// Position of object
	Vector2D GetPosition();
	// Set position of object
	void SetPosition(Vector2D position);

	// Returns if the object is active
	bool IsActive() const;
	// Returns if the object can be deleted
	bool CanDelete() const;
	// Set the object to active
	void Activate(); 
	// Set the object to inactive
	void Deactivate(); 
	// Remove pointers to Render, Collision, etc, then set object to CAN_DELETE
	void DeleteObject(); 

	// Update the object calling all components of the object that aren't nullptrs,
	// only doing Render if the game is currently frozen
	void Update(HUD* pHUD, float frameTime, bool isFrozen);

	// The current SoundFX to use
	SoundFX* GetSoundFX();

	// Input component of object
	InputComponent* GetInputComponent();
	// Physics component of object
	PhysicsComponent* GetPhysicsComponent();
	// Render component of object
	RenderComponent* GetRenderComponent();
	// Collision component of object
	CollisionComponent* GetCollisionComponent();
	// message component of object
	MessageComponent* GetMessageComponent();
};
