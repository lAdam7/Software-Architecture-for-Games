#include "UpgradeMenu.h"
#include "mydrawengine.h"
#include "myinputs.h"
#include "gamecode.h"
#include <string>

void UpgradeMenu::Update(float frameTime, HUD* pHUD)
{
	MyDrawEngine* mDE = MyDrawEngine::GetInstance();

	Rectangle2D currentView;
	currentView = mDE->GetViewport();

	Vector2D centerBackground = Vector2D(currentView.GetTopLeft().XValue, currentView.GetCentre().YValue);

	Rectangle2D background;
	background.PlaceAt(centerBackground + Vector2D(0, -350), centerBackground + Vector2D(500, 350));
	mDE->FillRect(background, MyDrawEngine::DARKBLUE);
	
	
	mDE->WriteText(background.GetTopLeft() + Vector2D(30, -25), L"UPGRADES", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][11] = { L"RESUME", L"HEALTH", L"SHIELD" };

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		Vector2D startingPos = background.GetTopLeft() + Vector2D(30, -50 + (-200 * (float)i));
		if (i == 0)
		{
			Rectangle2D healthUprade;
			healthUprade.PlaceAt(startingPos + Vector2D(0, -50), startingPos + Vector2D(440, -160));
			mDE->FillRect(healthUprade, MyDrawEngine::GREY);
			mDE->WriteText(healthUprade.GetCentre() + Vector2D(-175, 15), L"RESUME", MyDrawEngine::WHITE);
		}
		else if (i == 1) // HEALTH
		{
			std::wstring strHealthLevel = L"Health Level: " + std::to_wstring(m_currentHealthLevel + 1);
			mDE->WriteText(startingPos + Vector2D(0, 0), strHealthLevel.c_str(), MyDrawEngine::WHITE);
			Rectangle2D healthUprade;
			healthUprade.PlaceAt(startingPos + Vector2D(0, -50), startingPos + Vector2D(440, -160));
			mDE->FillRect(healthUprade, MyDrawEngine::GREY);
			if (m_currentHealthLevel == HEALTHUPGRADES - 1) // MAXXED OUT
			{
				mDE->WriteText(healthUprade.GetCentre() + Vector2D(-175, 15), L"MAX LEVEL", MyDrawEngine::WHITE);
			}
			else
			{
				mDE->WriteText(healthUprade.GetCentre() + Vector2D(-175, 50), L"UPGRADE HEALTH", MyDrawEngine::WHITE);
				std::wstring strPoints = std::to_wstring(m_healthUpgradesPoints[m_currentHealthLevel+1]) + L" points";
				mDE->WriteText(healthUprade.GetCentre() + Vector2D(-175, 0), strPoints.c_str(), MyDrawEngine::WHITE);
			}
		}
		else if (i == 2) // HEALTH
		{
			std::wstring strHealthLevel = L"Shield Level: " + std::to_wstring(m_currentShieldLevel + 1);
			mDE->WriteText(startingPos + Vector2D(0, 0), strHealthLevel.c_str(), MyDrawEngine::WHITE);
			Rectangle2D healthUprade;
			healthUprade.PlaceAt(startingPos + Vector2D(0, -50), startingPos + Vector2D(440, -160));
			mDE->FillRect(healthUprade, MyDrawEngine::GREY);
			if (m_currentShieldLevel == SHIELDUPGRADES - 1) // MAXXED OUT
			{
				mDE->WriteText(healthUprade.GetCentre() + Vector2D(-175, 15), L"MAX LEVEL", MyDrawEngine::WHITE);
			}
			else
			{
				mDE->WriteText(healthUprade.GetCentre() + Vector2D(-175, 50), L"UPGRADE SHIELD", MyDrawEngine::WHITE);
				std::wstring strPoints = std::to_wstring(m_shieldUpgradesPoints[m_currentShieldLevel + 1]) + L" points";
				mDE->WriteText(healthUprade.GetCentre() + Vector2D(-175, 0), strPoints.c_str(), MyDrawEngine::WHITE);
			}
		}
	}
	Vector2D startingPos = background.GetTopLeft() + Vector2D(30, -50 + (-200 * m_selectedOption));
	Rectangle2D selectedBar;
	selectedBar.PlaceAt(startingPos + Vector2D(0, -50), startingPos + Vector2D(15, -160));
	mDE->FillRect(selectedBar, MyDrawEngine::WHITE);
	/*
	std::wstring strHealthLevel = L"Health Level: " + std::to_wstring(m_currentHealthLevel + 1);
	mDE->WriteText(background.GetTopLeft() + Vector2D(30, -75), strHealthLevel.c_str(), MyDrawEngine::GREY);
	Rectangle2D healthUprade;
	healthUprade.PlaceAt(background.GetTopLeft() + Vector2D(30, -120), background.GetTopLeft() + Vector2D(470, -220));
	mDE->FillRect(healthUprade, MyDrawEngine::GREY);
	*/

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	if (pInputs->NewKeyPressed(DIK_UP))
	{
		m_selectedOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_selectedOption++;
	}
	if (m_selectedOption < 0)
	{
		m_selectedOption = NUMOPTIONS - 1;
	}
	else if (m_selectedOption >= NUMOPTIONS)
	{
		m_selectedOption = 0;
	}

	if (pInputs->NewKeyPressed(DIK_RETURN))
	{
		if (m_selectedOption == 0) // RESUME
		{
			Game::instance.GetObjectManager().FreezeGame(false);
		}
		else if (m_selectedOption == 1 && m_currentHealthLevel != (HEALTHUPGRADES - 1)) // UPGRADE HEALTH
		{
			m_currentHealthLevel++;
			pHUD->SetMaxHealth(m_healthUpgradesHealth[m_currentHealthLevel]);
			pHUD->Heal();
		}
		else if (m_selectedOption == 2 && m_currentShieldLevel != (SHIELDUPGRADES - 1)) // UPGRADE SHIELD
		{
			m_currentShieldLevel++;
			pHUD->SetMaxShield(m_shieldUpgradesShield[m_currentShieldLevel]);
		}
	}

};

/*
Rectangle2D buttonBar;
		buttonBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 1600, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
		mDE->FillRect(buttonBar, MyDrawEngine::GREY);
		MyDrawEngine::GetInstance()->WriteText(550, 350 + (140 * (float)i), options[i], MyDrawEngine::WHITE, newFont);
		if (i == m_menuOption)//+ (-200 * (float)i) + (-10 * (float)i) - 70 + 108
		{
			Rectangle2D selectedBar;
			selectedBar.PlaceAt(Vector2D(currentView.GetTopLeft().XValue + 900, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) + 70 - (110 * (float)i)), Vector2D(currentView.GetTopLeft().XValue + 925, currentView.GetTopLeft().YValue - 690 - (140 * (float)i) - 70 - (110 * (float)i)));
			mDE->FillRect(selectedBar, MyDrawEngine::WHITE);
		}
*/