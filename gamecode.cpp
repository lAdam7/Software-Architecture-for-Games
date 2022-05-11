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
#include "KeyCollisionComponent.h"
#include "RecurringCollisionComponent.h"

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

// Get the object manager singleton
ObjectManager& Game::GetObjectManager()
{
	return om;
};

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
	case RUNNING:           // Playing the actual game
		err = Update();
		if (om.IsFrozen()) // Freeze game, but still runs Render tos how background stuff
		{
			if (om.GetFreezeScreen() == Type_Freeze::BUY) // Buy / upgrade shop
				um->Update((float)gt.mdFrameTime, pHUD);
			else if (om.GetFreezeScreen() == Type_Freeze::DEFEAT) // Player died
				WonDefeatMenu(true);
			else if (om.GetFreezeScreen() == Type_Freeze::WON) // Player killed boss
				WonDefeatMenu(false);
			else if (om.GetFreezeScreen() == Type_Freeze::PAUSE) // Player pressed ESC to pause
				PauseMenu();
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

// When player has either died or won render UI on screen
ErrorType Game::WonDefeatMenu(bool died)
{
	// Code for a basic pause menu
	MyDrawEngine* mDE = MyDrawEngine::GetInstance();
	mDE->WriteText(450, 220, (died) ? L"YOU DIED" : L"YOU WON", (died) ? MyDrawEngine::RED : MyDrawEngine::GREEN, newFont); // depending if died or killed the boss

	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][11] = { L"RESTART", L"MAIN MENU", L"EXIT"}; 

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		Rectangle2D currentView;
		currentView = mDE->GetViewport(); // Cam pos

		Rectangle2D buttonBar;
		buttonBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 1600, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
		mDE->FillRect(buttonBar, MyDrawEngine::GREY);
		MyDrawEngine::GetInstance()->WriteText(550, 350 + (140 * i), options[i], MyDrawEngine::WHITE, newFont);
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
		MyDrawEngine::GetInstance()->WriteText(550, 350 + (140 * i), options[i], MyDrawEngine::WHITE, newFont);
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
			om.FreezeGame(false);
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
		MyDrawEngine::GetInstance()->WriteText(550, 350 + (140 * i), options[i], MyDrawEngine::WHITE, newFont);
		if (i == m_menuOption)
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
	um = new UpgradeMenu(); //Initialize the upgrade menu UI ready
	om.FreezeGame(false); // Default game not frozen

	// Create the map walls and floors, adding collision if its a wall
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
	om.CreateMultiple(L"floor_0.png", 4, 10, 128.0f, false, Type::WALL, Vector2D(-384, 2492));
	om.CreateMultiple(L"wall_0.png", 1, 10, 128.0f, true, Type::WALL, Vector2D(-704, 2492));
	om.CreateMultiple(L"wall_0.png", 1, 10, 128.0f, true, Type::WALL, Vector2D(-64, 2492));
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(-1344, 3068));
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(576, 3068));
	om.CreateMultiple(L"floor_0.png", 24, 15, 128.0f, false, Type::WALL, Vector2D(-384, 4092));
	om.CreateMultiple(L"wall_0.png", 10, 1, 128.0f, true, Type::WALL, Vector2D(-1280, 4988));
	om.CreateMultiple(L"wall_0.png", 10, 1, 128.0f, true, Type::WALL, Vector2D(512, 4988));
	om.CreateMultiple(L"wall_0.png", 1, 16, 128.0f, true, Type::WALL, Vector2D(-1984, 4028));
	om.CreateMultiple(L"wall_0.png", 1, 16, 128.0f, true, Type::WALL, Vector2D(1216, 4028));
	om.CreateMultiple(L"wall_0.png", 8, 1, 128.0f, true, Type::WALL, Vector2D(-384, 6012));
	om.CreateMultiple(L"wall_0.png", 1, 8, 128.0f, true, Type::WALL, Vector2D(-960, 5564));
	om.CreateMultiple(L"wall_0.png", 1, 8, 128.0f, true, Type::WALL, Vector2D(192, 5564));
	om.CreateMultiple(L"floor_0.png", 8, 7, 128.0f, false, Type::WALL, Vector2D(-384, 5500));
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(-1088, 3452));
	om.CreateMultiple(L"wall_0.png", 1, 9, 128.0f, true, Type::WALL, Vector2D(-1600, 4092));
	om.CreateMultiple(L"wall_0.png", 1, 9, 128.0f, true, Type::WALL, Vector2D(-448, 3964));
	om.CreateMultiple(L"wall_0.png", 12, 1, 128.0f, true, Type::WALL, Vector2D(128, 4604));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(-704, 4732));
	om.CreateMultiple(L"wall_0.png", 4, 1, 128.0f, true, Type::WALL, Vector2D(-1280, 4604));
	om.CreateMultiple(L"wall_0.png", 4, 1, 128.0f, true, Type::WALL, Vector2D(-1024, 4220));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(-1216, 3964));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(-832, 3964));
	om.CreateMultiple(L"wall_0.png", 9, 1, 128.0f, true, Type::WALL, Vector2D(192, 3452));
	om.CreateMultiple(L"wall_0.png", 1, 7, 128.0f, true, Type::WALL, Vector2D(832, 3836));
	om.CreateMultiple(L"wall_0.png", 5, 1, 128.0f, true, Type::WALL, Vector2D(192, 4220));
	om.CreateMultiple(L"wall_0.png", 1, 3, 128.0f, true, Type::WALL, Vector2D(448, 3964));

	// Create explosive
	GameObject* explosion = om.Create(L"Explosive");
	// Set explosive position
	explosion->SetPosition(Vector2D(-986, -290));

	// Init soundFX and set in object manager
	pSoundFX = new SoundFX();
	pSoundFX->LoadSounds();
	om.SetSoundFX(pSoundFX);

	// Init the HUD for the health, points, shield and ammo tracking
	pHUD = new HUD();
	
	// Create the player legs sprite
	GameObject* pFeet = om.Create(L"PlayerLegs");
	// Default spawn location
	pFeet->SetPosition(Vector2D(-896, 1536));
	// Link the main character (torso), to the Legs for position sync
	PlayerLegsInputComponent* pLegsInput = dynamic_cast<PlayerLegsInputComponent*>(pFeet->GetInputComponent());
	// Create the player main/torso, and set to the Playerlegs
	pLegsInput->SetMainCharacter(Game::instance.GetObjectManager().Create(L"PlayerMain"));

	// Create first door
	GameObject* pDoor1 = om.CreateMultiple(L"door_0.png", 2, 1, 128.0f, true, Type::DOOR, Vector2D(-384, 1788));
	DoorInputComponent* pDoorInput1 = dynamic_cast<DoorInputComponent*>(pDoor1->GetInputComponent());
	pDoorInput1->SetKeysRequired(1); // Keys required to open the door
	pDoorInput1->SetPlayer(pFeet); // Magnitude location check

	GameObject* pKey1 = om.CreateKey(pDoor1);
	pKey1->SetPosition(Vector2D(-496, 174));

	// Create second big door
	GameObject* pDoor2 = om.CreateMultiple(L"door_0.png", 4, 1, 128.0f, true, Type::DOOR, Vector2D(-384, 4988));
	DoorInputComponent* pDoorInput2 = dynamic_cast<DoorInputComponent*>(pDoor2->GetInputComponent());
	pDoorInput2->SetKeysRequired(2); // Keys required to open door
	pDoorInput2->SetPlayer(pFeet);

	GameObject* pKey2 = om.CreateKey(pDoor2);
	pKey2->SetPosition(Vector2D(-1024, 4092));

	GameObject* pKey3 = om.CreateKey(pDoor2);
	pKey3->SetPosition(Vector2D(255, 4092));
	
	// Create enemies in the game
	om.CreateEnemy(Vector2D(-896, 325), pFeet, 1.5708f);
	om.CreateEnemy(Vector2D(-896, 225), pFeet, 1.5708f);
	om.CreateEnemy(Vector2D(-896, 125), pFeet, 1.5708f);
	om.CreateEnemy(Vector2D(-505, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-505, -259), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-405, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-405, -259), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-305, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-305, -259), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-205, -135), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(-205, -259), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(874, 16), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(874, 216), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(874, 416), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(874, 616), pFeet, -1.5708f);
	om.CreateEnemy(Vector2D(378, 1509), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(278, 1509), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(178, 1509), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(406, 1005), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(30, 1005), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(-520, 1005), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(-520, 577), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(30, 577), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(406, 577), pFeet, 0.0f);
	om.CreateEnemy(Vector2D(187, 187), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(87, 187), pFeet, 3.1416);
	om.CreateEnemy(Vector2D(-13, 187), pFeet, 3.1416);
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
	// Create the boss
	om.CreateBoss(pFeet);

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
	if(KEYPRESSED(VK_ESCAPE) && !om.IsFrozen()) // Pause menu, freeze game
	{
		if (!escapepressed)
			om.FreezeGame(true, Type_Freeze::PAUSE);
		escapepressed=true;
	}
	else
		escapepressed=false;


   // Your code goes here *************************************************
   // *********************************************************************

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	if (!om.IsFrozen() && pInputs->KeyPressed(DIK_B)) // Open shop to upgrade
	{
		om.FreezeGame(true, Type_Freeze::BUY);
	}

	gt.mark();

	om.UpdateAll((float)gt.mdFrameTime, pHUD); // Update all objects

	pHUD->Update(); // Update HUD after render of objects

	if (timer > 1000) // Delete all marked on a timer
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
