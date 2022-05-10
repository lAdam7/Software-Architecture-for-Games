#pragma once
#include "mydrawengine.h"
#include <list>

/*
* The animation struct stored in a list for 
* each object with a AnimatedRenderComponent
*
* @author W19023403
*/

// Animation data structure, for each type of animation e.g. Walk, Run
struct Animation
{
	float m_currentImage; // Image shown
	float m_animationSpeed; // Speed of the animation
	std::vector<PictureIndex> m_images; // All the images required for the animation
	int m_nextAnimation; // Animation to call once finished
};