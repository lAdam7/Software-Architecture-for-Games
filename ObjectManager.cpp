#include "ObjectManager.h"
#include "PlayerLegsInputComponent.h"
#include "AnimatedRenderComponent.h"
#include "CollisionComponent.h"
#include "PlayerMainInputComponent.h"
#include "BulletPhysicsComponent.h"
#include "EnemyGameObject.h"
#include "EnemyPhysicsComponent.h"
#include "RecurringRenderComponent.h"
#include "ExplosionCollisionComponent.h"
#include "ShieldCollisionComponent.h"
#include "EnemyMessageComponent.h"
#include "BossPhysicsComponent.h"
#include "DropCollisionComponent.h"
#include "ExplosiveCollisionComponent.h"
#include "EnemyCollisionComponent.h"
#include "BulletCollisionComponent.h"
#include "RecurringCollisionComponent.h"
#include "DoorInputComponent.h"
#include "KeyInputComponent.h"
#include "KeyCollisionComponent.h"

/*
* Managing all objects in the game, storing all
* the game objects that exist and managing deletion,
* sending messages and sounds
*
* @author W19023403
*/

// Draw the given shape onto the screen, used for testing purposes
// to show the collision boxes of all objects and the interaction 
// that occurs
void ObjectManager::DrawHitbox(IShape2D& shape)
{
	if (typeid(shape) == typeid(Circle2D)) // circle collision object
	{
		Circle2D circle = dynamic_cast<Circle2D&>(shape);
		MyDrawEngine::GetInstance()->FillCircle(circle.GetCentre(), circle.GetRadius(), MyDrawEngine::CYAN);
	}
	else if (typeid(shape) == typeid(Rectangle2D)) // rectangle collision object
	{
		Rectangle2D rectangle = dynamic_cast<Rectangle2D&>(shape);
		MyDrawEngine::GetInstance()->FillRect(rectangle, MyDrawEngine::CYAN);
	}
};

// Create a object based off a string sent, if the string matches a object
// it will be created, possible ones are: Bullet, PlayersLegs, PlayerMain,
// Enemy, Boss, Shield, Explosive, Explosion or Drop. Adds to the object
// list ready for updates
GameObject* ObjectManager::Create(std::wstring name)
{
	GameObject* pNewObject = nullptr;

	// Collision types
	Circle2D circle;
	Rectangle2D rectangle;

	if (name == L"Bullet") // Create a bullet
	{
		BulletPhysicsComponent* pBulletPhysics = new BulletPhysicsComponent();
		RenderComponent* pBulletRender = new RenderComponent(L"bullet.png");
		CollisionComponent* pBulletCollision = new BulletCollisionComponent(circle, 10.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			pBulletPhysics, // Keep bullet moving on the velocity of the bullet
			pBulletRender, // Render on screen
			pBulletCollision, // Object collision
			nullptr,
			Type::BULLET
		);
	}
	else if (name == L"PlayerLegs") // Different sprite, controls the direction moving and rotation of the player
	{
		RenderComponent* pPlayerLegsRender = new AnimatedRenderComponent();
		PlayerLegsInputComponent* pPlayerLegsInput = new PlayerLegsInputComponent(pPlayerLegsRender);
		CollisionComponent* pCollisionComponent = new CollisionComponent(circle, 50.0f);

		pNewObject = new GameObject(
			pSoundFX,
			pPlayerLegsInput, //  Direction and rotation of the player, controls forcefield when enabled
			nullptr,
			pPlayerLegsRender, // Render on screen
			pCollisionComponent, // Object collision
			nullptr,
			Type::PLAYER
		);
		pNewObject->SetAngle(3.1416f); // Have player default facing downwards (due to the map)
	}
	else if (name == L"PlayerMain") // Different sprite, controls the gun / shooting aspect of the player
	{
		RenderComponent* pPlayerMainRender = new AnimatedRenderComponent();
		PlayerMainInputComponent* pPlayerMainInput = new PlayerMainInputComponent(pPlayerMainRender);

		pNewObject = new GameObject(
			pSoundFX,
			pPlayerMainInput, // Shooting and gun mechanics, reload
			nullptr,
			pPlayerMainRender, // Render on screen
			nullptr,
			nullptr,
			Type::IGNOREOBJ // Not required for any collision or type checks, the legs control collisions
		);
		pNewObject->Activate();
	}
	else if (name == L"Enemy") // Main zombie / enemy sprite
	{
		RenderComponent* pEnemyRender = new AnimatedRenderComponent();
		EnemyPhysicsComponent* pEnemyPhysics = new EnemyPhysicsComponent(pEnemyRender);
		CollisionComponent* pCollisionComponent = new EnemyCollisionComponent(circle, 50.0f);
		MessageComponent* pEnemyMessage = new EnemyMessageComponent();

		pNewObject = new EnemyGameObject(
			pSoundFX,
			nullptr,
			pEnemyPhysics, // Detection of the player, checking if in sight, damage cooldown and setting sprite up
			pEnemyRender, // Render on screen
			pCollisionComponent, // Object collision
			pEnemyMessage, // Can receive messages, used for when playing is reloading to use speed boost and when a bullet is fired
			Type::ENEMY
		);
	}
	else if (name == L"Boss") // Zombie boss sprite
	{
		RenderComponent* pEnemyRender = new AnimatedRenderComponent();
		BossPhysicsComponent* pEnemyPhysiscs = new BossPhysicsComponent(pEnemyRender);
		CollisionComponent* pCollisionComponent = new EnemyCollisionComponent(circle, 60.0f);

		pNewObject = new EnemyGameObject(
			pSoundFX,
			nullptr,
			pEnemyPhysiscs, // Detection of the player, checking if in sight, damage cooldown and setting sprite up
			pEnemyRender, // Render on screen
			pCollisionComponent, // Object collision
			nullptr,
			Type::ENEMY_BOSS
		);
		pNewObject->SetPosition(Vector2D(-384, 5500)); // Boss spawn location in the top room
		pNewObject->SetScale(0.2f); // Sprite too big, reduce size

		EnemyGameObject* test = dynamic_cast<EnemyGameObject*>(pNewObject);
		test->SetMaxHealth(1000.0f); // Health of the boss
		test->Heal(); // Enemy is healed to the max health
		
	}
	else if (name == L"Shield") // Shield that is located on the player when drop is picked-up
	{
		RenderComponent* pShieldRender = new RenderComponent(L"shield.png");
		CollisionComponent* pShieldCollision = new ShieldCollisionComponent(circle, 140.0f);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pShieldRender, // Render on screen
			pShieldCollision, // Object collision
			nullptr,
			Type::SHIELD
		);
	}
	else if (name == L"Explosive") // Explosive, if shot it explodes
	{
		RenderComponent* pExplosionRender = new RenderComponent(L"explosive.png");
		CollisionComponent* pExplosionCollision = new ExplosiveCollisionComponent(circle, 30.0f);


		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pExplosionRender, // Render on screen
			pExplosionCollision, // Object collision (if bullet hits, it explodes)
			nullptr,
			Type::EXPLOSIVE
		);
	}
	else if (name == L"Explosion") // Works alongside Explosive, if hit the Explosion is put on-top of it
	{
		RenderComponent* pExplosionRender = new AnimatedRenderComponent();
		AnimatedRenderComponent* circle = dynamic_cast<AnimatedRenderComponent*>(pExplosionRender);
		Circle2D circleV;
		CollisionComponent* pExplosionCollision = new ExplosionCollisionComponent(circleV, 300.0f, 0.3f);

		// Only requires one animation, add all images to the animationrender, set to reapeat
		// speed and set the animation to active
		int explode;
		explode = circle->NewAnimation();
		circle->AddImage(explode, L"explosion1.bmp");
		circle->AddImage(explode, L"explosion2.bmp");
		circle->AddImage(explode, L"explosion3.bmp");
		circle->AddImage(explode, L"explosion4.bmp");
		circle->AddImage(explode, L"explosion5.bmp");
		circle->AddImage(explode, L"explosion6.bmp");
		circle->AddImage(explode, L"explosion7.bmp");
		circle->AddImage(explode, L"explosion8.bmp");

		circle->NextAnimation(explode, explode);
		circle->SetAnimationSpeed(explode, 10.0f);
		circle->SetCurrentAnimation(explode);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pExplosionRender, // Render on screen
			pExplosionCollision, // Object collision, damages opponents
			nullptr,
			Type::EXPLOSION
		);
	}
	else if (name == L"Drop") // Drops, randomly dropped upon a zombies death, randomly selects the type of drop
	{
		int randomNumber = 1 + (rand() % 3); // 3 different drops, set imageName and dropType depending on this value
		std::wstring imageName = (randomNumber == 1) ? L"shotgun.png" : (randomNumber == 2) ? L"bouncing_bullet.png" : L"shield_drop.png";
		Type_Drop dropType = (randomNumber == 1) ? Type_Drop::SHOTGUN : (randomNumber == 2) ? Type_Drop::BOUNCING_BULLET : Type_Drop::FORCEFIELD;

		RenderComponent* pDropRender = new RenderComponent(imageName.c_str());
		DropCollisionComponent* pDropCollision = new DropCollisionComponent(circle, 50.0f, dropType);

		pNewObject = new GameObject(
			pSoundFX,
			nullptr,
			nullptr,
			pDropRender, // Render on screen
			pDropCollision, // If player collides, they can have the picked up powerup
			nullptr,
			Type::POWERUP
		);
	}
	else
	{
		// Given name doesn't exist output error
		ErrorLogger::Write(L"Could not create item: ");
		ErrorLogger::Writeln(name.c_str());
	}
	if (pNewObject != nullptr)
		AddObject(pNewObject); // Add object to the list, if one has been created

	return pNewObject;
};

// Create the enemy, passed spawn position, target player and angle of the player on spawn
void ObjectManager::CreateEnemy(Vector2D position, GameObject* pTarget, float angle)
{
	GameObject* pEnemy = Create(L"Enemy");
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pEnemy);
	pEnemyObject->SetTarget(pTarget);
	pEnemyObject->SetPosition(position);
	pEnemy->SetAngle(angle);
};

// Create the boss, always has a default spawn location
void ObjectManager::CreateBoss(GameObject* pTarget)
{
	GameObject* pEnemy = Create(L"Boss");
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pEnemy);
	pEnemyObject->SetTarget(pTarget);
	pEnemyObject->SetDamage(60.0f);
};

// Create a key, sending a pointer to the door it unlocks
GameObject* ObjectManager::CreateKey(GameObject* pDoor)
{
	Circle2D circle;

	KeyInputComponent* pInputKey = new KeyInputComponent(pDoor);
	RenderComponent* pRenderKey = new RenderComponent(L"key.png");
	CollisionComponent* pCollisionKey = new KeyCollisionComponent(circle, 50.0f);

	GameObject* pNewKey = new GameObject(
		pSoundFX,
		pInputKey,
		nullptr,
		pRenderKey,
		pCollisionKey,
		nullptr,
		Type::KEY
	);

	AddObject(pNewKey); 

	return pNewKey;
};

// Repeating the same texture in a grid-type system, used for walls and floors
GameObject* ObjectManager::CreateMultiple(const wchar_t* filename, int repeatX, int repeatY, float imageSize, bool collision, Type type, Vector2D position)
{
	RecurringRenderComponent* pRecurringWallRender = new RecurringRenderComponent(filename);
	pRecurringWallRender->SetRepeatX(repeatX); // X grid size
	pRecurringWallRender->SetRepeatY(repeatY); // Y grid size
	pRecurringWallRender->SetImageSize(imageSize); // image size
	
	CollisionComponent* pRecurringWallCollision = nullptr;
	Rectangle2D rectangle;
	if (collision) // Create the total collision size, if the object should have collision
		pRecurringWallCollision = new RecurringCollisionComponent(rectangle, imageSize * repeatX, imageSize * repeatY);

	InputComponent* pInput = nullptr;
	if (type == Type::DOOR)
		pInput = new DoorInputComponent();

	GameObject* pNewObject = new GameObject(
		pSoundFX,
		pInput,
		nullptr,
		pRecurringWallRender, // Render on screen
		pRecurringWallCollision, // Wall collision
		nullptr,
		type
	);

	pNewObject->SetPosition(position); // Set to given position
	AddObject(pNewObject); // Add to object list

	return pNewObject;
};

// Get the SoundFX
SoundFX* ObjectManager::GetSoundFX()
{
	return pSoundFX;
};

// Used in start of gamecode, when sound is created store in the
// object manager for repeat use
void ObjectManager::SetSoundFX(SoundFX* pSound)
{
	pSoundFX = pSound;
};

// Add object to the game object list
void ObjectManager::AddObject(GameObject* pNewObject)
{
	if (pNewObject != nullptr)
	{
		m_pObjectList.push_back(pNewObject);
	}
};

// Send a message, to all objects that have a messagign component 
// and doesn't have listening disabled for the event
void ObjectManager::TransmitMessage(Message msg)
{
	for (GameObject* pNext : m_pObjectList) // every object
	{
		if (pNext && pNext->GetMessageComponent() && pNext->GetMessageComponent()->IsListening())
		{
			pNext->GetMessageComponent()->HandleMessage(pNext, msg); // Send message, the component can check if it's relevent to them
		}
	}
};

// Called every frame to update all objects in the list and call the components
// that it has
void ObjectManager::UpdateAll(double frameTime, HUD* pHUD)
{
	MyDrawEngine::GetInstance()->WriteInt(50, 50, m_pObjectList.size(), MyDrawEngine::GREEN);

	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = m_pObjectList.begin(); it1 != m_pObjectList.end(); it1++)
	{
		if ((*it1)) // not nullptr
		{
			(*it1)->Update(pHUD, (float)frameTime, IsFrozen()); // Call update of the GameObject, send IsFrozen() so it will only Render if frozen
			if ((*it1)->IsCollidable() && !IsFrozen()) // Object is collidable and game is not frozen check collisions
			{
				if (SHOWHITBOX) // Debug tool, draw the collision on the screen
				{
					DrawHitbox((*it1)->GetCollisionComponent()->GetShape(*it1));
				}
				for (it2 = next(it1); it2 != m_pObjectList.end(); it2++)
				{
					if ((*it2) && (*it2)->IsCollidable()) // object 2 is collidable
					{
						if ((*it1) && (*it2) &&
							(*it1)->IsActive() && (*it2)->IsActive() && // both are active, not inactive or marked for delete
							(*it1)->GetCollisionComponent()->GetShape((*it1)).Intersects((*it2)->GetCollisionComponent()->GetShape((*it2)))) // shapes intersects
						{
							(*it1)->GetCollisionComponent()->HandleCollision(pHUD, (*it1), (*it2)); // Send collision message to first object
							(*it2)->GetCollisionComponent()->HandleCollision(pHUD, (*it2), (*it1)); // Send collision message to second object
						}
					}
				}
			}

		}
	}
};

// Delete all objects in the list
void ObjectManager::DeleteAll()
{
	for (GameObject* obj : m_pObjectList)
	{
		obj->DeleteObject();
		delete obj;
		obj = nullptr;
	}
	m_pObjectList.clear();
};

// Delete all objects in the list that are not currently active
void ObjectManager::DeleteAllInactive()
{
	for (GameObject*& obj : m_pObjectList)
	{
		if (!obj->IsActive())
		{
			obj->DeleteObject();
			delete obj;
			obj = nullptr;
		}
	}
	m_pObjectList.remove(nullptr);
};

// Delete all objects in the list, that are marked as CAN_DELETE
// called every n frames in gamecode
void ObjectManager::DeleteAllMarked()
{
	for (GameObject*& obj : m_pObjectList)
	{
		if (obj->CanDelete())
		{
			obj->DeleteObject();
			delete obj;
			obj = nullptr;
		}
	}
	m_pObjectList.remove(nullptr);
};

// Freeze/UnFreeze game and the reasoning of the state
void ObjectManager::FreezeGame(bool freezeGame, Type_Freeze freezeScreen)
{
	m_freezeGame = freezeGame;
	m_freezeScreen = freezeScreen;
};

// Freeze/Unfeeze game
void ObjectManager::FreezeGame(bool freezeGame)
{
	m_freezeGame = freezeGame;
};
// If currently frozen
bool ObjectManager::IsFrozen() const
{
	return m_freezeGame;
};
// The reason for the freeze
Type_Freeze ObjectManager::GetFreezeScreen()
{
	return m_freezeScreen;
};

// Check if the given shape intersects with a wall, if not has direct sight to the player
// so enemy can attack/move to the player
bool ObjectManager::EnemyDirectSight(IShape2D& shape)
{
	for (GameObject* pNext : m_pObjectList)
	{
		if (pNext->GetType() == Type::WALL) // Check all walls in the object list
		{
			if (pNext && pNext->IsCollidable() && pNext->IsActive() && pNext->GetCollisionComponent()->GetShape(pNext).Intersects(shape)) // Collidable and intersection check
			{
				return false;
			}
		}
	}
	return true;
};