#include "Asteroid.h";
#include "myinputs.h"

void Asteroid::Initialise(Vector2D startingPosition)
{
	position = startingPosition;
	angle = 0;

	const wchar_t* images[4] = { L"rock1.bmp", L"rock2.bmp", L"rock3.bmp", L"rock4.bmp"};

	LoadImg(images[rand()%4]);
	
	active = true;
};

void Asteroid::Update(double frameTime)
{

};