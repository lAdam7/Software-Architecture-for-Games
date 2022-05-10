#include "PlayerLegsInputComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"
#include "gamecode.h"

/*
* Inherits from the InputComponent for the PlayerLegs
* used to detect movement around the map and the rotation
* of the player, and positioning shield if active to keep it
* always on top
*
* @author W19023403
*/

// Constructor setup the animations
PlayerLegsInputComponent::PlayerLegsInputComponent(RenderComponent* pRender)
{
	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pRender);
	idle = animate->NewAnimation(); // Create idle animation only 1 image
	animate->AddImage(idle, L"idle_0.png");
	animate->SetCurrentAnimation(idle); // default

	walk = animate->NewAnimation(); // Create walk animation
	animate->AddImage(walk, L"survivorRun_0.png");
	animate->AddImage(walk, L"survivorRun_1.png");
	animate->AddImage(walk, L"survivorRun_2.png");
	animate->AddImage(walk, L"survivorRun_3.png");
	animate->AddImage(walk, L"survivorRun_4.png");
	animate->AddImage(walk, L"survivorRun_5.png");
	animate->AddImage(walk, L"survivorRun_6.png");
	animate->AddImage(walk, L"survivorRun_7.png");
	animate->AddImage(walk, L"survivorRun_8.png");
	animate->AddImage(walk, L"survivorRun_9.png");
	animate->AddImage(walk, L"survivorRun_10.png");
	animate->AddImage(walk, L"survivorRun_11.png");
	animate->AddImage(walk, L"survivorRun_12.png");
	animate->AddImage(walk, L"survivorRun_13.png");
	animate->AddImage(walk, L"survivorRun_14.png");
	animate->AddImage(walk, L"survivorRun_15.png");
	animate->AddImage(walk, L"survivorRun_16.png");
	animate->AddImage(walk, L"survivorRun_17.png");
	animate->AddImage(walk, L"survivorRun_18.png");
	animate->AddImage(walk, L"survivorRun_19.png");
	animate->NextAnimation(walk, walk);
	animate->SetAnimationSpeed(walk, 17.0f);
	
	m_state = CharState::IDLE; // Set to IDLE walking
}

// Detect player input for moving player around and rotating, placing shield if not nullptr
void PlayerLegsInputComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	const float positionAmount = 600.0f * frameTime;
	const float rotationAmount = 5.0f * frameTime;
	
	CharState current = CharState::IDLE;

	if (pInputs->KeyPressed(DIK_LEFT)) // Left-Key
	{
		pObject->SetAngle(pObject->GetAngle() - rotationAmount);
	}
	if (pInputs->KeyPressed(DIK_RIGHT)) // Right-Key
	{
		pObject->SetAngle(pObject->GetAngle() + rotationAmount);
	}
	if (pInputs->KeyPressed(DIK_W)) // W
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(0, positionAmount));
	}
	if (pInputs->KeyPressed(DIK_S)) // S
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(0, -positionAmount));
	}
	if (pInputs->KeyPressed(DIK_A)) // A
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(-positionAmount, 0));
	}
	if (pInputs->KeyPressed(DIK_D)) // D
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(positionAmount, 0));
	}

	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());
	if (current != m_state) { // state change
		if (current == CharState::IDLE)
		{
			animate->SetCurrentAnimation(idle);
		}
		else // walking
		{
			animate->SetCurrentAnimation(walk);
		}
		m_state = current;
	}

	animate->Animate(frameTime); // Update the movement of the sprite

	if (GetMainCharacter()) // Not nullptr
	{ // Place main characer directly on-top of the legs
		GetMainCharacter()->SetPosition(pObject->GetPosition());
		GetMainCharacter()->SetAngle(pObject->GetAngle());
	}

	if (GetShield()) // Not nullptr
	{ // Place shield directly on-top of the legs
		GetShield()->SetPosition(pObject->GetPosition());
	}

	MyDrawEngine::GetInstance()->theCamera.PlaceAt(pObject->GetPosition()); // Place camera on players position

	if (pHUD->GetCurrentHealth() <= 0) // Player has died
	{
		pHUD->SetActive(false); // Set HUD to inactive
		GetMainCharacter()->DeleteObject(); // Delete the main character
		pObject->DeleteObject(); // Delete legs charcter
		Game::instance.GetObjectManager().FreezeGame(true, Type_Freeze::DEFEAT); // Freeze the game with dead message
	}
};

// Set the main character
void PlayerLegsInputComponent::SetMainCharacter(GameObject* pObject)
{
	m_mainCharacter = pObject;
};
// Get the main character
GameObject* PlayerLegsInputComponent::GetMainCharacter()
{
	return m_mainCharacter;
};

// Set the shield
void PlayerLegsInputComponent::SetShield(GameObject* pObject)
{
	m_shield = pObject;
};
// Get the shield
GameObject* PlayerLegsInputComponent::GetShield()
{
	return m_shield;
};