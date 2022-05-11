#include "SoundFX.h"

void SoundFX::LoadSounds()
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();

	m_Shot = pSoundEngine->LoadWav(L"Bullet.wav");
	MySoundEngine::GetInstance()->SetVolume(m_Shot, -800);

	m_Explosions[0] = pSoundEngine->LoadWav(L"explosion1.wav");
	m_Explosions[1] = pSoundEngine->LoadWav(L"explosion2.wav");
	m_Explosions[2] = pSoundEngine->LoadWav(L"explosion3.wav");
	m_Explosions[3] = pSoundEngine->LoadWav(L"explosion4.wav");
	m_Explosions[4] = pSoundEngine->LoadWav(L"explosion5.wav");
};

void SoundFX::PlayShot()
{
	MySoundEngine::GetInstance()->Play(m_Shot);
};

void SoundFX::PlayExplosion()
{
	MySoundEngine::GetInstance()->Play(m_Explosions[rand() % NUMEXPLOSIONSOUNDS]);
};