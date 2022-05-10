#pragma once
#include "GameObject.h"
#include "HUD.h"
#include <list>

enum class Type_Freeze { PAUSE, WON, DEFEAT, BUY };
/*
* Managing all objects in the game, storing all
* the game objects that exist and managing deletion,
* sending messages and sounds
* 
* @author W19023403 
*/
class ObjectManager
{		
private:
	// All game objects stored as a pointer that will be iterated in Update() every frame
	std::list<GameObject*> m_pObjectList;

	// Pointer sound, remains abstract to play audio during the game
	SoundFX* pSoundFX;

	// Controls the rendering of the hitbox / collision space for each object (Testing tool)
	const bool SHOWHITBOX = false;
	// Draws the hitbox regardless of shape and draws on screen (Testing tool)
	void DrawHitbox(IShape2D& shape);
	
	// The game currently frozen, rendering still occurs, but no input, messaging, physics or collisions
	bool m_freezeGame;
	// The reasoning for the freeze can be either Paused game, Won game, Died or currently in upgrade menu
	Type_Freeze m_freezeScreen;
public:
	// Add a object to the list for updating, creation dealt outside the object manager requires pointer to the object
	void AddObject(GameObject* pObject);

	// Create an object, send the type of object, creation dealt within the object manager
	GameObject* Create(std::wstring name);

	// Set the SoundFX to the object manager to keep it abstract
	void SetSoundFX(SoundFX* pSound);

	// Send a message to all objects that have a pointer to a MessagingComponent
	void TransmitMessage(Message msg);

	// Update all objects in the game, calling the Input, Physics, Render, 
	// and Collision components if they exist, and check for any collision,
	// only Render is called if the game is currently frozen
	void UpdateAll(double frameTime, HUD* pHUD);

	// Delete all objects in the list, used for restarting game and exiting game
	void DeleteAll();
	// Delete all objects in the list, that are not currently active 
	void DeleteAllInactive();
	// Delete all objects in the list, that are marked as ready to delete, called
	// every n frames, as continous iteration isn't required
	void DeleteAllMarked();

	// Create a texture that needs to be repeated, worked on a grid based system so is used for creating
	// the floors and walls, reduced iterations required in the object list and means only one collision
	// component is required for the entire object
	void CreateMultiple(const wchar_t* filename, int repeatX, int repeatY, float imageSize, bool collision, Type type, Vector2D position);
	// Simplify creation of enemies, allowing data for position, target and angle to be created within one
	// line, rather than using Create and setting values within the gamecode would increase code required
	void CreateEnemy(Vector2D pos, GameObject* pTarget, float angle);
	// Create the boss in the final room
	void CreateBoss(GameObject* pTarget);

	// Freeze the game, but continue rendering needs boolean to freeze and unfreeze
	// additionally the reason for the freeze can be passed through
	void FreezeGame(bool freeze, Type_Freeze m_freezeScreen);
	// Freze / unfreeze the game
	void FreezeGame(bool freeze);
	// Returns if the game is currently frozen
	bool IsFrozen() const;
	// Returns the reason the screen is frozen
	Type_Freeze GetFreezeScreen();

	// Checking the object list if the sent shape has direct
	// sight to the player, without any collision in between
	// if so the enemy can move to the location of the player
	bool EnemyDirectSight(IShape2D& shape);
};