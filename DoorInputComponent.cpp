#include "DoorInputComponent.h"
#include "GameObject.h"

DoorInputComponent::DoorInputComponent(int keysRequired)
{
	m_keysRequired = keysRequired;
}

bool DoorInputComponent::GotKeys() const
{
	return (m_keysGot >= m_keysRequired);
};

void DoorInputComponent::PickedKey()
{
	m_keysGot = m_keysGot + 1;
};

void DoorInputComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	//std::wstring strHealth = L"Health: " + std::to_wstring((int)GetCurrentHealth()) + L" / " + std::to_wstring((int)GetMaxHealth());
	if ((pObject->GetPosition() - pPlayer->GetPosition()).magnitude() < 200.0f)
	{
		MyDrawEngine* mDE = MyDrawEngine::GetInstance();
		std::wstring strMessage;
		if (!GotKeys())
		{
			if (m_keysRequired > 1)
			{
				strMessage = L"You have " + std::to_wstring(m_keysGot) + L" / " + std::to_wstring(m_keysRequired) + L" keys to open this door!";
			}
			else
			{
				strMessage = L"You need a key to open this door!";
			}	
		}
		else
		{
			strMessage = L"Press Q to open the door!";

			MyInputs* pInputs = MyInputs::GetInstance();
			pInputs->SampleKeyboard();

			if (pInputs->KeyPressed(DIK_Q))
			{
				pObject->DeleteObject();
			}
		}
		mDE->WriteText(100, 300, strMessage.c_str(), MyDrawEngine::WHITE);
	}
};