#pragma once
#include "mysoundengine.h"

class SoundFX
{
private:
	static const int NUMEXPLOSIONSOUNDS = 5;
	SoundIndex m_Explosions[NUMEXPLOSIONSOUNDS];
	SoundIndex m_Thrust;
	SoundIndex m_Shot;
	bool m_EnginePlaying;
public:
	void LoadSounds();
	void PlayShot();
	void PlayExplosion();
	void StartEngineSound();
	void StopEngineSound();
	void SetEngineVolume(int volume);
};