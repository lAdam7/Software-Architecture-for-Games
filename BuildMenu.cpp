#include "BuildMenu.h"
#include "myinputs.h"
#include "spaceship.h"
#include "ObjectManager.h"
#include "gamecode.h"

void BuildMenu::setPlacing(bool status)
{
	placing = status;
}

bool BuildMenu::getPlacing() {
	return placing;
}

void BuildMenu::Grid() {
	const int CELLSIZE = 75;
	const int GRIDSIZE = 50;

	MyDrawEngine* pDE = MyDrawEngine::GetInstance();

	for (int x = 0; x < GRIDSIZE+1; x++) 
	{
		for (int y = 0; y < GRIDSIZE+1; y++)
		{
			pDE->DrawLine(Vector2D(-(GRIDSIZE*CELLSIZE)/2, (y*CELLSIZE - (GRIDSIZE * CELLSIZE) / 2)), Vector2D((GRIDSIZE * CELLSIZE) / 2, (y * CELLSIZE - (GRIDSIZE * CELLSIZE) / 2)), 412412);

			pDE->DrawLine(Vector2D((x*CELLSIZE) - ((GRIDSIZE*CELLSIZE)/2), -((GRIDSIZE*CELLSIZE)/2)), Vector2D((x*CELLSIZE) - ((GRIDSIZE*CELLSIZE)/2), ((GRIDSIZE*CELLSIZE)/2)), 412412);
		}
	}

}

void BuildMenu::buildInterface()
{
	Grid();


	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][15] = { L"Place Wall", L"Cancel" };

	// Display the options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;
		if (i == bmOptionSelected)
		{
			colour = MyDrawEngine::WHITE;
		}
		MyDrawEngine::GetInstance()->WriteText(10, 300 + 50 * i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	if (pInputs->NewKeyPressed(DIK_UP))
	{
		bmOptionSelected--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		bmOptionSelected++;
	}
	if (bmOptionSelected < 0)
	{
		bmOptionSelected = NUMOPTIONS-1;
	}
	else if (bmOptionSelected >= NUMOPTIONS)
	{
		bmOptionSelected = 0;
	}

	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (bmOptionSelected == 0)   // Place X
		{
			
			Spaceship* pShip = new Spaceship();
			pShip->Initialise(Vector2D(0, 0));
				//om.AddObject(pShip);
			
			Game::instance.GetObjectManager().AddObject(pShip);
			placingObj = pShip;
			//placingObj = new Spaceship();
			//placingObj->Initalise(Vector2D(0, 0));
		}

		if (bmOptionSelected == 1)	// Cancel
		{
			setPlacing(false);
		}
	}
}