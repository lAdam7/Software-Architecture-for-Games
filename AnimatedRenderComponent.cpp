#include "AnimatedRenderComponent.h"
#include "GameObject.h"

void AnimatedRenderComponent::SetCurrentAnimation(int anim)
{
	m_currentAnimation = anim;
};

void AnimatedRenderComponent::Update(GameObject* pObject)
{
	if (pObject->IsActive())
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(pObject->GetPosition(), animations[m_currentAnimation].m_images[int(m_animationTimer)], 1.0f, pObject->GetAngle());
	}
};

void AnimatedRenderComponent::Animate(float frameTime)
{
	Animation& anim = animations[m_currentAnimation];
	m_animationTimer += anim.m_animationSpeed;// *frameTime;
	if (m_animationTimer >= anim.m_images.size())
	{
		m_currentAnimation = anim.m_nextAnimation;
		m_animationTimer = 0;
	}
};

int AnimatedRenderComponent::NewAnimation()
{
	Animation* temp = new Animation();
	animations.push_back(*temp);
	delete temp;
	temp = nullptr;
	return animations.size()-1;
};

void AnimatedRenderComponent::AddImage(int index, const wchar_t* filename)
{
	animations[index].m_images.push_back(MyDrawEngine::GetInstance()->LoadPicture(filename));
};

void AnimatedRenderComponent::DeleteObject()
{
	animations.clear();
};

/*
void AnimatedRenderComponent::Update(GameObject* pObject)
{
	if (pObject->IsActive() && images.size() > 0)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(pObject->GetPosition(), images[m_currentImage], 1.0f, pObject->GetAngle());
	}
};

void AnimatedRenderComponent::AddImage(const wchar_t* filename)
{
	images.push_back(MyDrawEngine::GetInstance()->LoadPicture(filename));
};

void AnimatedRenderComponent::SetCurrentImage(int index)
{
	index = m_currentImage + 1;
	if (index < 0)
		m_currentImage = images.size() - 1;
	if (index >= images.size())
		m_currentImage = 0;
	else
		m_currentImage = index;
};*/