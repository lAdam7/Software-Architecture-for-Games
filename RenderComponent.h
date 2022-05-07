#pragma once
#include "mydrawengine.h"
#include "Animation.h"

class GameObject;

class RenderComponent
{
protected:
	PictureIndex image;

public:
	RenderComponent(const wchar_t* filename);
	RenderComponent() = default;
	virtual ~RenderComponent();

	virtual void AddImage(const wchar_t* filename);
	virtual void AddImage(Animation* ani, const wchar_t* filename);
	virtual void SetCurrentImage(int image);
	virtual void Update(GameObject* pObject);
};