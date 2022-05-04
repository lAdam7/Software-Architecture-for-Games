#pragma once
#include "InputComponent.h"
#include "RenderComponent.h"

enum class CharState { IDLE, WALKING };
class PlayerLegsInputComponent : public InputComponent
{
public:
	PlayerLegsInputComponent(RenderComponent* pRender);
	void Update(GameObject* pObject, float frameTime) override;
	CharState m_state;
	float animation = 4.0f;

	float shieldCounter = 0.0f;

	GameObject* mainCharacter;
	GameObject* shield;

	int idle, walk;
};