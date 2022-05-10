#include "PlayerMainInputComponent.h"
#include "GameObject.h"

/*
* Main character, always placed directly on the legs render,
* handles shooting the gun and management of bullets
*
* @author W19023403
*/

// Constructor setup the gun and the animations for the main character
PlayerMainInputComponent::PlayerMainInputComponent(RenderComponent* pRender)
{
	SetAnimatedRenderComponent(dynamic_cast<AnimatedRenderComponent*>(pRender));
	
	m_gun = new Gun();

	rifle = GetAnimatedRenderComponent()->NewAnimation(); // Holding a rifle animation
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_0.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_1.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_2.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_3.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_4.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_5.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_6.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_7.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_8.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_9.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_10.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_11.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_12.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_13.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_14.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_15.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_16.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_17.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_18.png");
	GetAnimatedRenderComponent()->AddImage(rifle, L"survivorRifle_19.png");

	GetAnimatedRenderComponent()->NextAnimation(rifle, rifle); // Repeat
	GetAnimatedRenderComponent()->SetAnimationSpeed(rifle, 10.0f); // Time
	GetAnimatedRenderComponent()->SetCurrentAnimation(rifle); // First animation to run

	reload = GetAnimatedRenderComponent()->NewAnimation(); // Reloading rifle animation
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_0.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_1.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_2.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_3.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_4.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_5.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_6.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_7.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_8.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_9.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_10.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_11.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_12.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_13.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_14.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_15.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_16.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_17.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_18.png");
	GetAnimatedRenderComponent()->AddImage(reload, L"survivorReload_19.png");

	GetAnimatedRenderComponent()->NextAnimation(reload, rifle); // Once reloaded, go back to rifle animation
	GetAnimatedRenderComponent()->SetAnimationSpeed(reload, 7.0f); // Speed of reload animation


	GetGun()->SetBulletDelay(0.5f); // Bullet delay
	GetGun()->SetClipSize(12); // Max clip size
	GetGun()->SetReloadTime(2.0f); // Time to reload
}

// Override Update for InputComponent, updates the animation and updates the gun
void PlayerMainInputComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	if (GetGun()->Update(pHUD, frameTime)) // reload animation start
	{
		GetAnimatedRenderComponent()->SetCurrentAnimation(reload);
	}

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	
	if (pInputs->KeyPressed(DIK_SPACE))// Shoot
	{
		if (GetGun()->Fire(pObject->GetPosition(), pObject->GetAngle(), pObject, reload)) // False == not enough bullets start reload
		{
			GetAnimatedRenderComponent()->SetCurrentAnimation(reload);
		}
	}

	pHUD->SetMaxAmmo(GetGun()->GetClipSize()); // max clip size
	pHUD->SetAmmo(GetGun()->GetClipSizeCounter()); // current clip size

	GetAnimatedRenderComponent()->Animate(frameTime); // Update the animation
};

// Get the gun
Gun* PlayerMainInputComponent::GetGun()
{
	return m_gun;
};

// Set the RenderComponent to the animated for easier access
void PlayerMainInputComponent::SetAnimatedRenderComponent(AnimatedRenderComponent* pRender)
{
	m_pAnimatedRenderComponent = pRender;
};
// Get the AnimatedRenderComponent
AnimatedRenderComponent* PlayerMainInputComponent::GetAnimatedRenderComponent()
{
	return m_pAnimatedRenderComponent;
};