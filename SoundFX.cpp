#include "SoundFX.h"

/*
* SoundFX only one is ever created,
* and a pointer is passed to all
* objects, to utilize
*
* @author W19023403
*/

// Load all sounds, on game startup
void SoundFX::LoadSounds()
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();

	// Bullet
	m_Shot = pSoundEngine->LoadWav(L"Bullet.wav");
	MySoundEngine::GetInstance()->SetVolume(m_Shot, -800);

	// Explosion
	m_Explosions[0] = pSoundEngine->LoadWav(L"explosion1.wav");
	m_Explosions[1] = pSoundEngine->LoadWav(L"explosion2.wav");
	m_Explosions[2] = pSoundEngine->LoadWav(L"explosion3.wav");
	m_Explosions[3] = pSoundEngine->LoadWav(L"explosion4.wav");
	m_Explosions[4] = pSoundEngine->LoadWav(L"explosion5.wav");
};

// Fire a shot
void SoundFX::PlayShot()
{
	MySoundEngine::GetInstance()->Play(m_Shot);
};
// Play a random explosion
void SoundFX::PlayExplosion()
{
	MySoundEngine::GetInstance()->Play(m_Explosions[rand() % NUMEXPLOSIONSOUNDS]);
};