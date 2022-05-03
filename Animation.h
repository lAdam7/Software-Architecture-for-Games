#pragma once
#include "mydrawengine.h"
#include <list>

struct Animation
{
	float m_currentImage;
	float m_animationSpeed = 0.05f;
	std::vector<PictureIndex> m_images;
	int m_nextAnimation;
};