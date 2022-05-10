#include "AnimatedRenderComponent.h"
#include "GameObject.h"

/*
* Inherits from the RenderCommpoent to handle animated objects
* that follow a sprite format to change the image depending on the
* set times
*
* @author W19023403
*/

// Change to a different animation, reset the timer
void AnimatedRenderComponent::SetCurrentAnimation(int anim)
{
	m_currentAnimation = anim;
	m_animationTimer = 0;
};

// Get the current animation being played
int AnimatedRenderComponent::GetCurrentAnimation()
{
	return m_currentAnimation;
};

// Render the image the timer is currently actively on
void AnimatedRenderComponent::Update(GameObject* pObject)
{
	if (pObject->IsActive())
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(pObject->GetPosition(), animations[m_currentAnimation].m_images[int(m_animationTimer)], pObject->GetScale(), pObject->GetAngle());
	}
};

// Increment animation counter, if exceedes the images call the next animation set 
// within that animation, may just repeat itself or call a different animation
void AnimatedRenderComponent::Animate(float frameTime)
{
	Animation& anim = animations[m_currentAnimation];
	m_animationTimer += anim.m_animationSpeed * frameTime;
	if (m_animationTimer >= anim.m_images.size())
	{
		m_currentAnimation = anim.m_nextAnimation;
		m_animationTimer = 0;
	}
};

// Create a new animation, returns the location of the animation
int AnimatedRenderComponent::NewAnimation()
{
	Animation* temp = new Animation();
	animations.push_back(*temp);
	delete temp;
	temp = nullptr;
	return animations.size()-1;
};

// Add a new image to the location of the animation passed
void AnimatedRenderComponent::AddImage(int index, const wchar_t* filename)
{
	animations[index].m_images.push_back(MyDrawEngine::GetInstance()->LoadPicture(filename));
};

// Set animation speed of the location of the animation passed
void AnimatedRenderComponent::SetAnimationSpeed(int index, float speed)
{
	animations[index].m_animationSpeed = speed;
};

// Set the next animation, of the location of the animation passed for when it's finished showing all sprites
void AnimatedRenderComponent::NextAnimation(int currentIndex, int nextIndex)
{
	animations[currentIndex].m_nextAnimation = nextIndex;
};

// Deletion of the object, clear animations list to prevent memory leaks
void AnimatedRenderComponent::DeleteObject()
{
	animations.clear();
};