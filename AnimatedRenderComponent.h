#pragma once
#include "mydrawengine.h"
#include "RenderComponent.h"
#include "Animation.h"

class GameObject;

class AnimatedRenderComponent : public RenderComponent
{
private:
	std::vector<Animation> animations;
	int m_currentAnimation = 0;
	float m_animationTimer = 0.0f;

	//std::vector<PictureIndex> images;
	//int m_currentImage;
public:
	void SetCurrentAnimation(int anim);
	void Update(GameObject* pObject);
	void Animate(float frameTime);

	int NewAnimation();
	void AddImage(int index, const wchar_t* filename);
	void DeleteObject();
	void SetAnimationSpeed(int index, float speed);
	void NextAnimation(int currentIndex, int nextIndex);
	int GetCurrentAnimation();

	//void SetCurrentImage(int index) override;

	//void Update(GameObject* pObject) override;
};