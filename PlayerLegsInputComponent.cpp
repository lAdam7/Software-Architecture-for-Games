#include "PlayerLegsInputComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"
#include "gamecode.h"

PlayerLegsInputComponent::PlayerLegsInputComponent(RenderComponent* pRender)
{
	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pRender);
	idle = animate->NewAnimation();
	animate->AddImage(idle, L"idle_0.png");

	animate->SetCurrentAnimation(idle);

	walk = animate->NewAnimation();
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
	
	m_state = CharState::IDLE;
}

void PlayerLegsInputComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	const float positionAmount = 600.0f * frameTime;
	const float rotationAmount = 5.0f * frameTime;
	
	CharState current = CharState::IDLE;

	if (pInputs->KeyPressed(DIK_LEFT))
	{
		pObject->SetAngle(pObject->GetAngle() - rotationAmount);
	}
	if (pInputs->KeyPressed(DIK_RIGHT))
	{
		pObject->SetAngle(pObject->GetAngle() + rotationAmount);
	}
	if (pInputs->KeyPressed(DIK_W))
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(0, positionAmount));
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(0, -positionAmount));
	}
	if (pInputs->KeyPressed(DIK_A))
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(-positionAmount, 0));
	}
	if (pInputs->KeyPressed(DIK_D))
	{
		current = CharState::WALKING;
		pObject->SetPosition(pObject->GetPosition() + Vector2D(positionAmount, 0));
	}
	if (pInputs->KeyPressed(DIK_F) && shieldCounter > 0.3f)
	{
		shieldCounter = 0.0f;
		
		if (shield != nullptr)
		{
			shield->DeleteObject();
			shield = nullptr;
		}
		else
		{
			shield = Game::instance.GetObjectManager().Create(L"Shield");
		}
	}
	shieldCounter += frameTime;

	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());
	if (current != m_state) {
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

	animate->Animate(frameTime);

	if (mainCharacter)
	{
		mainCharacter->SetPosition(pObject->GetPosition());
		mainCharacter->SetAngle(pObject->GetAngle());
	}

	if (shield)
		shield->SetPosition(pObject->GetPosition());

	MyDrawEngine::GetInstance()->theCamera.PlaceAt(pObject->GetPosition());

	if (pHUD->GetCurrentHealth() <= 0)
	{
		pHUD->SetActive(false);
		mainCharacter->DeleteObject();
		pObject->DeleteObject();	
	}
};