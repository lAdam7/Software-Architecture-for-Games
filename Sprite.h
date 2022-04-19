#pragma once
#include <list>
#include "vector2D.h"

class Sprite
{
private:
	const wchar_t* spriteImages;
	std::list<wchar_t*> pObjectList;
	bool isAnimated;
	enum class AnimationType;
public:
	Sprite();
	~Sprite();

	void setAnimationType(AnimationType type);

	void loadSprite(wchar_t* url, bool isAnimated);
	void DrawSprite(Vector2D position);
	void Animate_Sprite(int frames, AnimationType at);

};
