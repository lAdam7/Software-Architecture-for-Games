#pragma once
#include "GameObject.h"

class EnemyGameObject : public GameObject
{
public:
	using GameObject::GameObject;

	GameObject* pTarget;

	int health = 100;
};