#pragma once
#include "mydrawengine.h"
#include "Animation.h"

class GameObject;

/*
* Base RenderComponent, stores the image
* of each object, and renders on every frame
* its called
*
* @author W19023403
*/
class RenderComponent
{
protected:
	// The image to render
	PictureIndex image;
public:
	// Constructor, loads the file as an image
	RenderComponent(const wchar_t* filename);
	RenderComponent() = default;
	// Destructor
	virtual ~RenderComponent();

	// Image to be rendered
	virtual void AddImage(const wchar_t* filename);
	// Adding images to an animation, allows use for the AnimationRenderComponent
	virtual void AddImage(Animation* ani, const wchar_t* filename);
	// Setting images to an animation, allows use for the AnimationRenderComponent
	virtual void SetCurrentImage(int image);

	// Render the image onto screen
	virtual void Update(GameObject* pObject);

	// If object requires additional pointers to be removed for deletion of object
	virtual void DeleteObject();
};