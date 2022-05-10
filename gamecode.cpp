// GameCode.cpp		

#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "EnemyGameObject.h"
#include "PlayerLegsInputComponent.h"
#include "RecurringRenderComponent.h"
#include "DoorInputComponent.h"
#include "KeyInputComponent.h"
//#include "spaceship.h"
//#include "Asteroid.h"

//#include "Wall.h"

Game::Game()
{
   // No-op
	// Get the system time.
	unsigned seed = time(0);
	
	// Seed the random number generator.
	srand(seed);
}

Game::~Game()
{
   // No-op
}

Game Game::instance;    // Singleton instance


ObjectManager& Game::GetObjectManager()
{
	return om;
}

// This is repeated, called every frame.
// It will run either Update( ), MainMenu() or PauseMenu() depending on the
// game state
ErrorType Game::Main()
{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine= MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err=SUCCESS;

	switch (m_currentState)
	{
	case MENU:

		err = MainMenu();     // Menu at start of game
		break;
	case PAUSED:
		err = PauseMenu();   // Player has paused the game
		break;
	case RUNNING:           // Playing the actual game
		err = Update();
		if (om.IsFrozen())
		{
			if (om.GetFreezeScreen() == Type_Freeze::BUY)
				um->Update((float)gt.mdFrameTime, pHUD);
			if (om.GetFreezeScreen() == Type_Freeze::DEFEAT)
				DeadMenu();
		}
		break;
	case GAMEOVER:
		err = FAILURE;       // Error return causes the window loop to exit
	default:
		// Not a valid state
		err = FAILURE;       // Error return causes the window loop to exit
	}
	
	return err;
}

// Use to change the state of the game. Private function
void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}
}

// Starts the game engines - Draw Engine, Sound Engine, Input Engine - singletons
// This is called soon after the program runs
ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	newFont = MyDrawEngine::GetInstance()->AddFont(L"Arial", 44, true, false);
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}



// Terminates the game engines - Draw Engine, Sound Engine, Input Engine
// This is called just before the program exits
void Game::Shutdown()

{
   // Any clean up code here 





	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}




// **********************************************************************************************
// Placeholder menus  ***************************************************************************
// **********************************************************************************************

// Called each frame when in the pause state. Manages the pause menu
// which is currently a basic placeholder
ErrorType Game::DeadMenu()
{
	// Code for a basic pause menu
	MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	mDE->WriteText(450, 220, L"YOU DIED", MyDrawEngine::RED, newFont);

	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][11] = { L"RESTART", L"MAIN MENU", L"EXIT"};

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		Rectangle2D currentView;
		currentView = mDE->GetViewport();

		Rectangle2D buttonBar;
		buttonBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 1600, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
		mDE->FillRect(buttonBar, MyDrawEngine::GREY);
		MyDrawEngine::GetInstance()->WriteText(550, 350 + (140 * (float)i), options[i], MyDrawEngine::WHITE, newFont);
		if (i == m_menuOption)//+ (-200 * (float)i) + (-10 * (float)i) - 70 + 108
		{
			Rectangle2D selectedBar;
			selectedBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 925, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
			mDE->FillRect(selectedBar, MyDrawEngine::WHITE);
		}
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	// Get user input
	pInputs->SampleKeyboard();

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = NUMOPTIONS - 1;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = 0;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_menuOption == 0)      // Restart
		{
			EndOfGame();
			StartOfGame();
		}
		if (m_menuOption == 1)      // Main menu
		{
			EndOfGame();           // Clear up the game
			ChangeState(MENU);     // Go back to the menu
		}
		if (m_menuOption == 2) // exit
		{
			EndOfGame();
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}

// Called each frame when in the pause state. Manages the pause menu
// which is currently a basic placeholder
ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu
	MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	mDE->WriteText(450, 220, L"PAUSED", MyDrawEngine::WHITE, newFont);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"RESUME", L"MAIN MENU"};

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		Rectangle2D currentView;
		currentView = mDE->GetViewport();

		Rectangle2D buttonBar;
		buttonBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 1600, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
		mDE->FillRect(buttonBar, MyDrawEngine::GREY);
		MyDrawEngine::GetInstance()->WriteText(550, 350 + (140 * (float)i), options[i], MyDrawEngine::WHITE, newFont);
		if (i == m_menuOption)
		{
			Rectangle2D selectedBar;
			selectedBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 925, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
			mDE->FillRect(selectedBar, MyDrawEngine::WHITE);
		}
	}

	MyInputs* pInputs = MyInputs::GetInstance();

   // Get user input
	pInputs->SampleKeyboard();

   // Move choice up and down
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=NUMOPTIONS-1;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=0;
	}

   // If player chooses an option ....
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)      // Resume
		{
			ChangeState(RUNNING);  // Go back to running the game
		}
		if(m_menuOption ==1)      // main menu
		{
			EndOfGame();           // Clear up the game
			ChangeState(MENU);     // Go back to the menu
		}

	}

	return SUCCESS;
}

// Called each frame when in the menu state. Manages the menu
// which is currently a basic placeholder
ErrorType Game::MainMenu()
{
	MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	
	mDE->WriteText(450,220, L"MAIN MENU", MyDrawEngine::WHITE, newFont);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][15] = {L"START GAME", L"EXIT"};

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		Rectangle2D currentView;
		currentView = mDE->GetViewport();

		Rectangle2D buttonBar;
		buttonBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 1600, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
		mDE->FillRect(buttonBar, MyDrawEngine::GREY);
		MyDrawEngine::GetInstance()->WriteText(550, 350 + (140 * (float)i), options[i], MyDrawEngine::WHITE, newFont);
		if (i == m_menuOption)//+ (-200 * (float)i) + (-10 * (float)i) - 70 + 108
		{
			Rectangle2D selectedBar;
			selectedBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 925, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
			mDE->FillRect(selectedBar, MyDrawEngine::WHITE);
		}
	}
	
   // Get keyboard input
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=NUMOPTIONS-1;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=0;
	}

   // User selects an option
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption == 0)          // Play
		{  
			StartOfGame();             // Initialise the game
			ChangeState(RUNNING);      // Run it
		}

		if(m_menuOption == 1)          //Quit
		{
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}


// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************


// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame()
{
   // Code to set up your game *********************************************
   // **********************************************************************
	um = new UpgradeMenu();
	om.FreezeGame(false);

	om.CreateMultiple(L"floor_0.png", 16, 16, 128.0f, false, Type::WALL, Vector2D(0, 700));
	om.CreateMultiple(L"wall_0.png", 5, 1, 128.0f, true, Type::WALL, Vector2D(-832, 1788));
	om.CreateMultiple(L"wall_0.png", 11, 1, 128.0f, true, Type::WALL, Vector2D(448, 1788));
	om.CreateMultiple(L"wall_0.png", 1, 16, 128.0f, true, Type::WALL, Vector2D(-1088, 700));
	om.CreateMultiple(L"wall_0.png", 1, 16, 128.0f, true, Type::WALL, Vector2D(1088, 700));
	om.CreateMultiple(L"wall_0.png", 18, 1, 128.0f, true, Type::WALL, Vector2D(0, -388));
	om.CreateMultiple(L"wall_0.png", 1, 13, 128.0f, true, Type::WALL, Vector2D(-704, 892));
	om.CreateMultiple(L"wall_0.png", 12, 1, 128.0f, true, Type::WALL, Vector2D(0, -4));
	om.CreateMultiple(L"wall_0.png", 1, 8, 128.0f, true, Type::WALL, Vector2D(704, 572));
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(-64, 1276));
	om.CreateMultiple(L"wall_0.png", 8, 1, 128.0f, true, Type::WALL, Vector2D(-128, 380));
	om.CreateMultiple(L"wall_0.png", 8, 1, 128.0f, true, Type::WALL, Vector2D(128, 764));

	om.CreateMultiple(L"floor_0.png", 2, 1, 128.0f, false, Type::WALL, Vector2D(-384, 1788));
	om.CreateMultiple(L"floor_0.png", 4, 10, 128.0f, false, Type::WALL, Vector2D(-384, 1788+448+256));
	om.CreateMultiple(L"wall_0.png", 1, 10, 128.0f, true, Type::WALL, Vector2D(-384 - 320, 1788 + 448+256));
	om.CreateMultiple(L"wall_0.png", 1, 10, 128.0f, true, Type::WALL, Vector2D(-384 + 320, 1788 + 448+256));
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640, 1788 + 448 + 256 + 704 - 128));
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(-384 + 320 + 640, 1788 + 448 + 256 + 704 - 128));
	om.CreateMultiple(L"floor_0.png", 24, 15, 128.0f, false, Type::WALL, Vector2D(-384, 1788 + 448 + 256 + 1600));

	om.CreateMultiple(L"wall_0.png", 10, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 896, 1788 + 448 + 256 + 704 + 1792));
	om.CreateMultiple(L"wall_0.png", 10, 1, 128.0f, true, Type::WALL, Vector2D(-384 + 896, 1788 + 448 + 256 + 704 + 1792));
	om.CreateMultiple(L"wall_0.png", 1, 16, 128.0f, true, Type::WALL, Vector2D(-384 - 1600, 1788 + 448 + 256 + 1536));
	om.CreateMultiple(L"wall_0.png", 1, 16, 128.0f, true, Type::WALL, Vector2D(-384 + 1600, 1788 + 448 + 256 + 1536));
	om.CreateMultiple(L"wall_0.png", 8, 1, 128.0f, true, Type::WALL, Vector2D(-384, 1788 + 448 + 256 + 704 + 1792 + 1024));
	om.CreateMultiple(L"wall_0.png", 1, 8, 128.0f, true, Type::WALL, Vector2D(-384 - 576, 1788 + 448 + 256 + 704 + 1792 + 1024 - 448));
	om.CreateMultiple(L"wall_0.png", 1, 8, 128.0f, true, Type::WALL, Vector2D(-384 + 576, 1788 + 448 + 256 + 704 + 1792 + 1024 - 448));

	om.CreateMultiple(L"floor_0.png", 8, 7, 128.0f, false, Type::WALL, Vector2D(-384, 1788 + 448 + 256 + 704 + 1792 + 1024 - 448-64));


	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256, 1788 + 448 + 256 + 704 + 256));
	om.CreateMultiple(L"wall_0.png", 1, 9, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 - 512, 1788 + 448 + 256 + 704 + 256 + 640));
	om.CreateMultiple(L"wall_0.png", 1, 9, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 640, 1788 + 448 + 256 + 704 + 256 + 640 - 128));
	om.CreateMultiple(L"wall_0.png", 12, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 640 + 448 + 128, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 640 + 448 - 704, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 + 192 - 64));
	om.CreateMultiple(L"wall_0.png", 4, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 640 + 448 - 1280, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640));
	om.CreateMultiple(L"wall_0.png", 4, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 640 + 448 - 1280 + 256, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 640 + 448 - 1280 + 256 - 192, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 256));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 640 + 448 - 1280 + 256 + 192, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 256));
	
	
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 1216 + 64, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 768));
	om.CreateMultiple(L"wall_0.png", 1, 7, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 1216 + 64 + 640, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 768 + 384));

	om.CreateMultiple(L"wall_0.png", 5, 1, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 1216 + 64, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 768 + 768));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(-384 - 320 - 640 + 256 + 1216 + 320, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 768 + 768 - 256));

	GameObject* explosion = om.Create(L"Explosive");
	explosion->SetPosition(Vector2D(-986, -290));

	pSoundFX = new SoundFX();
	pSoundFX->LoadSounds();
	om.SetSoundFX(pSoundFX);

	pHUD = new HUD();
	
	GameObject* pFeet = om.Create(L"PlayerLegs");
	pFeet->SetPosition(Vector2D(-896, 1536));
	PlayerLegsInputComponent* pLegsInput = dynamic_cast<PlayerLegsInputComponent*>(pFeet->GetInputComponent());
	pLegsInput->mainCharacter = Game::instance.GetObjectManager().Create(L"PlayerMain");


	RecurringRenderComponent* pRecurringWallRender = new RecurringRenderComponent(L"door_0.png");
	pRecurringWallRender->SetRepeatX(2);
	pRecurringWallRender->SetRepeatY(1);
	pRecurringWallRender->SetImageSize(128.0f);

	Rectangle2D rectangle;
	CollisionComponent* pRecurringWallCollision = new CollisionComponent(rectangle, 128.0f * 2, 128.0f * 1);
	
	DoorInputComponent* pInputWall = new DoorInputComponent(1);
	pInputWall->pPlayer = pFeet;

	GameObject* pNewObject = new GameObject(
		pSoundFX,
		pInputWall,
		nullptr,
		pRecurringWallRender,
		pRecurringWallCollision,
		nullptr,
		Type::WALL
	);
	pNewObject->SetPosition(Vector2D(-384, 1788));
	om.AddObject(pNewObject);

	Circle2D circle;
	KeyInputComponent* pInputKey = new KeyInputComponent(pNewObject);
	RenderComponent* pRenderKey = new RenderComponent(L"key.png");
	CollisionComponent* pCollisionKey = new CollisionComponent(circle, 50.0f);


	GameObject* pNewKey = new GameObject(
		pSoundFX,
		pInputKey,
		nullptr,
		pRenderKey,
		pCollisionKey,
		nullptr,
		Type::KEY
	);
	pNewKey->SetPosition(Vector2D(-496, 174));
	om.AddObject(pNewKey);


	/////////////
	RecurringRenderComponent* pRecurringWallRender_B = new RecurringRenderComponent(L"door_0.png");
	pRecurringWallRender_B->SetRepeatX(4);
	pRecurringWallRender_B->SetRepeatY(1);
	pRecurringWallRender_B->SetImageSize(128.0f);

	CollisionComponent* pRecurringWallCollision_B = new CollisionComponent(rectangle, 128.0f * 4, 128.0f * 1);

	DoorInputComponent* pInputWall_B = new DoorInputComponent(2);
	pInputWall_B->pPlayer = pFeet;

	GameObject* pNewObject_B = new GameObject(
		pSoundFX,
		pInputWall_B,
		nullptr,
		pRecurringWallRender_B,
		pRecurringWallCollision_B,
		nullptr,
		Type::WALL
	);
	pNewObject_B->SetPosition(Vector2D(-384, 1788 + 448 + 256 + 704 + 1792));
	om.AddObject(pNewObject_B);

	////////////////



	KeyInputComponent* pInputKey_B = new KeyInputComponent(pNewObject_B);
	RenderComponent* pRenderKey_B = new RenderComponent(L"key.png");
	CollisionComponent* pCollisionKey_B = new CollisionComponent(circle, 50.0f);

	GameObject* pNewKey_B = new GameObject(
		pSoundFX,
		pInputKey_B,
		nullptr,
		pRenderKey_B,
		pCollisionKey_B,
		nullptr,
		Type::KEY
	);
	pNewKey_B->SetPosition(Vector2D(-384 - 320 - 640 + 256 + 640 + 448 - 1280 + 256, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 128));
	om.AddObject(pNewKey_B);

	KeyInputComponent* pInputKey_C = new KeyInputComponent(pNewObject_B);
	RenderComponent* pRenderKey_C = new RenderComponent(L"key.png");
	CollisionComponent* pCollisionKey_C = new CollisionComponent(circle, 50.0f);

	GameObject* pNewKey_C = new GameObject(
		pSoundFX,
		pInputKey_C,
		nullptr,
		pRenderKey_C,
		pCollisionKey_C,
		nullptr,
		Type::KEY
	);
	pNewKey_C->SetPosition(Vector2D(255, 1788 + 448 + 256 + 704 + 256 + 640 - 128 + 640 - 384 - 128));
	om.AddObject(pNewKey_C);


	
	//om.CreateEnemy(Vector2D(0, 0), pFeet); 1.5708
	//Below spawn
	om.CreateEnemy(Vector2D(-896, 325), pFeet, 1.5708f);
	om.CreateEnemy(Vector2D(-896, 225), pFeet, 1.5708f);
	om.CreateEnemy(Vector2D(-896, 125), pFeet, 1.5708f);
	
	//bottom
	om.CreateEnemy(Vector2D(-505, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-505, -259), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-405, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-405, -259), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-305, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-305, -259), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-205, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-205, -259), pFeet, 0.0f);

	//far right
	om.CreateEnemy(Vector2D(874, 16), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(874, 216), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(874, 416), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(874, 616), pFeet, -1.5708f);
	
	om.CreateEnemy(Vector2D(378, 1509), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(278, 1509), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(178, 1509), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(406, 1005), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(30, 1005), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(-520, 1005), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(-520, 577), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(30, 577), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(406, 577), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(187, 187), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(87, 187), pFeet, 1.5708f * 2);
	om.CreateEnemy(Vector2D(-13, 187), pFeet, 1.5708f * 2);
	
	om.CreateEnemy(Vector2D(-520, 2110), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(-268, 2110), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(-372, 2866), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(-1000, 3240), pFeet, 1.5708f*2);
	om.CreateEnemy(Vector2D(-1500, 3240), pFeet, 1.5708f*2);
	om.CreateEnemy(Vector2D(-1796, 3608), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(-1796, 4162), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(-1147, 4795), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-1020, 3924), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(-1404, 3924), pFeet, 1.5708f);
	om.CreateEnemy(Vector2D(-632, 3924), pFeet, 1.5708f);
	
	om.CreateEnemy(Vector2D(240, 3248), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(1023, 3248), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(1023, 3691), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(1023, 4039), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(258, 3954), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(-22, 3954), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-258, 4390), pFeet, 1.5708f*2);
	om.CreateEnemy(Vector2D(635, 3664), pFeet, 1.5708f);
	om.CreateEnemy(Vector2D(482, 4798), pFeet, 1.5708f*2);
	om.CreateEnemy(Vector2D(121, 4798), pFeet, 1.5708f*2);
	om.CreateEnemy(Vector2D(-243, 4798), pFeet, 1.5708f*2);

	om.CreateBoss(pFeet);

	for (int i = 0; i < 2; i++)
	{
		
		//GameObject* pAsteroid = om.Create(L"Asteroid");
		//int xPos = (rand() % (900 - -900 + 1) + -900);
		//int yPos = (rand() % (900 - -900 + 1) + -900);
		//pAsteroid->Initialise(Vector2D((float) xPos, (float) yPos), Vector2D(0, 0), pSoundFX);
	}

	gt.mark();
	gt.mark();


	return SUCCESS;
}


// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	// Check for entry to pause menu
	static bool escapepressed = true;
	if(KEYPRESSED(VK_ESCAPE) && !om.IsFrozen())
	{
		if(!escapepressed)
			ChangeState(PAUSED);
		escapepressed=true;
	}
	else
		escapepressed=false;


   // Your code goes here *************************************************
   // *********************************************************************

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	if (!om.IsFrozen() && pInputs->NewKeyPressed(DIK_B))
	{
		om.FreezeGame(true, Type_Freeze::BUY);
	}

	gt.mark();


	//MyInputs* pInputs = MyInputs::GetInstance();
	//pInputs->SampleMouse();
	
	//om.CheckAllCollisions();
	//om.DeleteAllMarked();

	om.UpdateAll((float)gt.mdFrameTime, pHUD);

	pHUD->Update();

	if (timer > 1000)
	{
		timer = 0;
		om.DeleteAllMarked();
	}
	timer++;

   // *********************************************************************
   // *********************************************************************

	return SUCCESS;
}

// Called when the player ends the game
// Currently this is done from the PAUSED state, when returning to the main menu
// but could be done by the gameplay programmer in other situations
// This will be used by the gameplay programmer to clean up
ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
   // Add code here to tidy up ********************************************
   // *********************************************************************
	om.DeleteAll();

	delete pSoundFX;
	pSoundFX = nullptr;

	delete pHUD;
	pHUD = nullptr;

	delete um;
	um = nullptr;
	
	return SUCCESS;
}
