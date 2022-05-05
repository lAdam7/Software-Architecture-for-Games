#include "PlayerMainInputComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"

PlayerMainInputComponent::PlayerMainInputComponent(RenderComponent* pRender)
{
	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pRender);
	
	rifle = animate->NewAnimation();
	animate->AddImage(rifle, L"survivorRifle_0.png");
	animate->AddImage(rifle, L"survivorRifle_1.png");
	animate->AddImage(rifle, L"survivorRifle_2.png");
	animate->AddImage(rifle, L"survivorRifle_3.png");
	animate->AddImage(rifle, L"survivorRifle_4.png");
	animate->AddImage(rifle, L"survivorRifle_5.png");
	animate->AddImage(rifle, L"survivorRifle_6.png");
	animate->AddImage(rifle, L"survivorRifle_7.png");
	animate->AddImage(rifle, L"survivorRifle_8.png");
	animate->AddImage(rifle, L"survivorRifle_9.png");
	animate->AddImage(rifle, L"survivorRifle_10.png");
	animate->AddImage(rifle, L"survivorRifle_11.png");
	animate->AddImage(rifle, L"survivorRifle_12.png");
	animate->AddImage(rifle, L"survivorRifle_13.png");
	animate->AddImage(rifle, L"survivorRifle_14.png");
	animate->AddImage(rifle, L"survivorRifle_15.png");
	animate->AddImage(rifle, L"survivorRifle_16.png");
	animate->AddImage(rifle, L"survivorRifle_17.png");
	animate->AddImage(rifle, L"survivorRifle_18.png");
	animate->AddImage(rifle, L"survivorRifle_19.png");
	

	animate->SetCurrentAnimation(rifle);

	gun.SetBulletDelay(0.5f);
	gun.SetClipSize(12);
	gun.SetReloadTime(3.0f);
}

void PlayerMainInputComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	gun.Update(pHUD, frameTime);

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();


	if (pInputs->KeyPressed(DIK_SPACE))
	{
		gun.Fire(pObject->GetPosition(), pObject->GetAngle());
	}

	pHUD->SetMaxAmmo(gun.GetClipSize());
	pHUD->SetAmmo(gun.GetClipSizeCounter());

	AnimatedRenderComponent* animate = dynamic_cast<AnimatedRenderComponent*>(pObject->GetRenderComponent());
	animate->Animate(frameTime);
};