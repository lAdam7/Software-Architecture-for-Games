#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class BuildMenu
{
private:
	bool placing;
	GameObject* placingObj;
	int bmOptionSelected;
public:
	void buildInterface();
	void setPlacing(bool placing);
	bool getPlacing();
	void Grid();
};