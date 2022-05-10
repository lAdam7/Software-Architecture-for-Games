#pragma once
#include "mydrawengine.h"
#include "RenderComponent.h"
#include "Animation.h"

class GameObject;

/*
* Inherits from the RenderCommpoent to handle animated objects
* that follow a sprite format to change the image depending on the
* set times
*
* @author W19023403
*/
class AnimatedRenderComponent : public RenderComponent
{
private:
	// Each sprite / animation type so can support multiple e.g. Walking and Attacking for the same object
	std::vector<Animation> animations;
	// Index of the active animation
	int m_currentAnimation = 0;
	// Timer for when to change to the next image
	float m_animationTimer = 0.0f;
public:
	// Change animation type e.g. Walking or Attacking
	void SetCurrentAnimation(int anim);

	// Draw the m_curretnAnimation index onto the screen
	void Update(GameObject* pObject) override;
	// Change to the next image, or if end of image go to the NextAnimation,
	// can be different or just repeat itself
	void Animate(float frameTime);

	// Create a new animation
	int NewAnimation();
	// Add image to the created animation
	void AddImage(int index, const wchar_t* filename);
	// Set the speed of the created animation
	void SetAnimationSpeed(int index, float speed);
	// Animation to call once the animation has finished, can call itself or switch to a different one
	void NextAnimation(int currentIndex, int nextIndex);
	
	// The current annimation type being played returns the int, e.g. Walk or Attack match int
	int GetCurrentAnimation();

	// Deleting the object, clear all the animations to prevent memory leaks
	void DeleteObject();
};