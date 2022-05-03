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

	switch(m_currentState)
	{
	case MENU:

		err= MainMenu();     // Menu at start of game
		break;
	case PAUSED:
		err = PauseMenu();   // Player has paused the game
		break;
	case RUNNING:           // Playing the actual game
		err= Update();
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
ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu

	MyDrawEngine::GetInstance()->WriteText(450,220, L"Paused", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

   // Display menu options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
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
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // If player chooses an option ....
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)      // Resume
		{
			ChangeState(RUNNING);  // Go back to running the game
		}
		if(m_menuOption ==1)      // Quit
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
	MyDrawEngine::GetInstance()->WriteText(450,220, L"Main menu", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][15] = {L"Start game", L"Test", L"Exit"};

   // Display the options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
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
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // User selects an option
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption == 0)          // Play
		{  
			StartOfGame();             // Initialise the game
			ChangeState(RUNNING);      // Run it
		}
		
		if (m_menuOption == 1)		   // map creator
		{
			StartOfGame();
			ChangeState(RUNNING);
		}

		if(m_menuOption == 2)          //Quit
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
	
	pSoundFX = new SoundFX();
	pSoundFX->LoadSounds();
	om.SetSoundFX(pSoundFX);

	//GameObject* pWall = om.Create(L"Wall");
	//pWall->Initialise(Vector2D(500, 500), Vector2D(0, 0), pSoundFX);
	
	/*
	for (int a = 0; a < 20; a++)
	{
		for (int x = 0; x < 7; x++)
		{
			for (int y = 0; y < 7; y++)
			{
				GameObject* pWall = om.Create(L"Wall");

				Wall& wall = dynamic_cast<Wall&>(*pWall);
				wall.SetImageQuick(L"floor_1.png");

				pWall->Initialise(Vector2D(256 * x, 256 * y), Vector2D(0, 0), pSoundFX);
			}
		}

		for (int x = 0; x < 7; x++)
		{
			GameObject* pWall = om.Create(L"Wall");

			Wall& wall = dynamic_cast<Wall&>(*pWall);
			wall.CanCollide(true);
			wall.SetImageQuick(L"wall_2.png");

			pWall->Initialise(Vector2D(256 * x, 1792), Vector2D(0, 0), pSoundFX);
		}

		for (int x = 0; x < 7; x++)
		{
			GameObject* pWall = om.Create(L"Wall");

			Wall& wall = dynamic_cast<Wall&>(*pWall);
			wall.CanCollide(true);
			wall.SetImageQuick(L"wall_1.png");

			pWall->Initialise(Vector2D(256 * x, 2048), Vector2D(0, 0), pSoundFX);
		}

		for (int y = 0; y < 9; y++)
		{
			GameObject* pWall = om.Create(L"Wall");

			Wall& wall = dynamic_cast<Wall&>(*pWall);

			wall.CanCollide(true);
			wall.SetAngle(3.141592653589793238f);
			wall.SetImageQuick(L"side_1.png");
			pWall->Initialise(Vector2D(-256, 256 * y), Vector2D(0, 0), pSoundFX);
		}

		for (int y = 0; y < 9; y++)
		{
			GameObject* pWall = om.Create(L"Wall");

			Wall& wall = dynamic_cast<Wall&>(*pWall);

			wall.CanCollide(true);
			wall.SetImageQuick(L"side_1.png");
			pWall->Initialise(Vector2D(1792, 256 * y), Vector2D(0, 0), pSoundFX);
		}

		for (int x = 0; x < 7; x++)
		{
			GameObject* pWall = om.Create(L"Wall");

			Wall& wall = dynamic_cast<Wall&>(*pWall);

			wall.CanCollide(true);
			wall.SetAngle(3.141592653589793238f * .5);
			wall.SetImageQuick(L"side_1.png");
			pWall->Initialise(Vector2D(256 * x, -258), Vector2D(0, 0), pSoundFX);
		}



	}*/

	GameObject* pFeet = om.Create(L"PlayerLegs");

	GameObject* pWall = om.Create(L"Wall");


	GameObject* pEnemy = om.Create(L"Enemy1");
	EnemyGameObject* pEnemyObject = dynamic_cast<EnemyGameObject*>(pEnemy);
	pEnemyObject->pTarget = pFeet;

	//pFeet->Initialise(Vector2D(0, 0), Vector2D(0 ,0), pSoundFX);

	//GameObject* pMouse = om.Create(L"Mouse");
	//pMouse->Initialise(Vector2D(0, 0), Vector2D(0, 0), pSoundFX);

	//pMouse = new Mouse();
	//pMouse->StartUp();
	
	for (int i = 0; i < 6; i++)
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
	if(KEYPRESSED(VK_ESCAPE))
	{
		if(!escapepressed)
			ChangeState(PAUSED);
		escapepressed=true;
	}
	else
		escapepressed=false;


   // Your code goes here *************************************************
   // *********************************************************************


	gt.mark();


	//MyInputs* pInputs = MyInputs::GetInstance();
	//pInputs->SampleMouse();
	
	//om.CheckAllCollisions();
	//om.DeleteAllMarked();

	om.UpdateAll(gt.mdFrameTime);

	om.DeleteAllMarked();
	
	//DeleteAllMarked
	// 
	//om.RenderAll(gt.mdFrameTime);

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

	

	return SUCCESS;
}

