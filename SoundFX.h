#pragma once
#include "mysoundengine.h"

/*
* SoundFX only one is ever created,
* and a pointer is passed to all
* objects, to utilize
*
* @author W19023403
*/
class SoundFX
{
private:
	static const int NUMEXPLOSIONSOUNDS = 5;
	// Array of explosion sounds, so can choose a random one
	SoundIndex m_Explosions[NUMEXPLOSIONSOUNDS];
	// Shot sound
	SoundIndex m_Shot;
public:
	// Load all sounds, on game startup
	void LoadSounds();
	// Fire a shot
	void PlayShot();
	// Play a random explosion
	void PlayExplosion();
};