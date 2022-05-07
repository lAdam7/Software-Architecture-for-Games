#include "PlayerMainInputComponent.h"
#include "GameObject.h"

PlayerMainInputComponent::PlayerMainInputComponent(RenderComponent* pRender)
{
	pAnimatedRenderComponent = dynamic_cast<AnimatedRenderComponent*>(pRender);
	
	rifle = pAnimatedRenderComponent->NewAnimation();
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_0.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_1.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_2.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_3.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_4.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_5.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_6.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_7.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_8.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_9.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_10.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_11.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_12.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_13.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_14.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_15.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_16.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_17.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_18.png");
	pAnimatedRenderComponent->AddImage(rifle, L"survivorRifle_19.png");

	pAnimatedRenderComponent->NextAnimation(rifle, rifle);
	pAnimatedRenderComponent->SetAnimationSpeed(rifle, 10.0f);
	pAnimatedRenderComponent->SetCurrentAnimation(rifle);

	reload = pAnimatedRenderComponent->NewAnimation();
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_0.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_1.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_2.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_3.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_4.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_5.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_6.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_7.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_8.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_9.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_10.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_11.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_12.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_13.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_14.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_15.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_16.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_17.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_18.png");
	pAnimatedRenderComponent->AddImage(reload, L"survivorReload_19.png");

	pAnimatedRenderComponent->NextAnimation(reload, rifle);
	pAnimatedRenderComponent->SetAnimationSpeed(reload, 7.0f);


	gun.SetBulletDelay(0.5f);
	gun.SetClipSize(12);
	gun.SetReloadTime(2.0f);
}

void PlayerMainInputComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	if (gun.Update(pHUD, frameTime)) // reload animation
	{
		pAnimatedRenderComponent->SetCurrentAnimation(reload);
	}

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();


	if (pInputs->KeyPressed(DIK_SPACE))
	{
		if (gun.Fire(pObject->GetPosition(), pObject->GetAngle(), pObject, reload)) // reload
		{
			pAnimatedRenderComponent->SetCurrentAnimation(reload);
		}
	}

	pHUD->SetMaxAmmo(gun.GetClipSize());
	pHUD->SetAmmo(gun.GetClipSizeCounter());

	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());
	animate->Animate(frameTime);
};