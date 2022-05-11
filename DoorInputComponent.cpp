#include "DoorInputComponent.h"
#include "GameObject.h"

/*
* Inherits from the InputComponent to detect when the player
* is close to the door, if so, and the player has the keys required
* for the door, it allows you to open it, if not a message is displayed
*
* @author W19023403
*/

// Constuctor set obtained key to 0 and the keys required as the parameter sent
DoorInputComponent::DoorInputComponent()
{
	m_keysGot = 0;
};

// Set the amount of keys needed to open the door
void DoorInputComponent::SetKeysRequired(int keysRequired)
{
	m_keysRequired = keysRequired;
};

// If the player has enough keys to open the door
bool DoorInputComponent::GotKeys() const
{
	return (m_keysGot >= m_keysRequired);
};
// Player picked up a key, increment by 1
void DoorInputComponent::PickedKey()
{
	m_keysGot = m_keysGot + 1;
};

// Get the player object
GameObject* DoorInputComponent::GetPlayer()
{
	return m_pPlayer;
};
// Set the player object
void DoorInputComponent::SetPlayer(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
};

// Override the Update, check if player is close enough to the door, display message and detect key to open door
void DoorInputComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	if ((pObject->GetPosition() - GetPlayer()->GetPosition()).magnitude() < 200.0f) // Close enough to the door
	{
		std::wstring strMessage;
		if (!GotKeys()) // Not got enough keys
		{
			if (m_keysRequired > 1) // Required multiple keys, display how many they have / the amount needed
			{
				strMessage = L"You have " + std::to_wstring(m_keysGot) + L" / " + std::to_wstring(m_keysRequired) + L" keys to open this door!";
			}
			else // Required one key, just message saying you need a key for this door
			{
				strMessage = L"You need a key to open this door!";
			}	
		}
		else // Got enough keys to open door display message to press Q
		{
			strMessage = L"Press Q to open the door!";

			MyInputs* pInputs = MyInputs::GetInstance();
			pInputs->SampleKeyboard();

			if (pInputs->KeyPressed(DIK_Q)) // Q Pressed, Delete the door, allows player to go through
			{
				pObject->DeleteObject();
			}
		}
		MyDrawEngine::GetInstance()->WriteText(100, 300, strMessage.c_str(), MyDrawEngine::WHITE); // Message to open the door
	}
};

//void DoorInputComponent::DeleteObject()
//{
	//delete m_pPlayer;
	//m_pPlayer = nullptr;
//};