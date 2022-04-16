#include "SoundFX.h"

void SoundFX::LoadSounds()
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();

	m_Shot = pSoundEngine->LoadWav(L"shoot.wav");
	m_Thrust = pSoundEngine->LoadWav(L"thrustloop2.wav");

	m_Explosions[0] = pSoundEngine->LoadWav(L"explosion1.wav");
	m_Explosions[1] = pSoundEngine->LoadWav(L"explosion2.wav");
	m_Explosions[2] = pSoundEngine->LoadWav(L"explosion3.wav");
	m_Explosions[3] = pSoundEngine->LoadWav(L"explosion4.wav");
	m_Explosions[4] = pSoundEngine->LoadWav(L"explosion5.wav");
}

void SoundFX::PlayShot()
{
	MySoundEngine::GetInstance()->Play(m_Shot);
}

void SoundFX::StartEngineSound()
{
	if (!m_EnginePlaying)
	{
		MySoundEngine::GetInstance()->Play(m_Thrust, true);
		m_EnginePlaying = true;
	}
}

void SoundFX::StopEngineSound()
{
	if (m_EnginePlaying)
	{
		MySoundEngine::GetInstance()->Stop(m_Thrust);
		m_EnginePlaying = false;
	}
}

void SoundFX::SetEngineVolume(int volume)
{
	volume = (volume - 100) * 35;
	MySoundEngine::GetInstance()->SetVolume(m_Thrust, volume);
}

void SoundFX::PlayExplosion()
{
	MySoundEngine::GetInstance()->Play(m_Explosions[rand()%NUMEXPLOSIONSOUNDS]);
}