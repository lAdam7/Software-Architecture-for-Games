#pragma once
#include "RenderComponent.h"

/*
* Inherits from the RenderComponent, allows for the same image
* to be placed next to each other in a grid based system,
* currently used for placing the floor and walls
*
* @author W19023403
*/
class RecurringRenderComponent : public RenderComponent
{
private:
	// The image size X and Y are always the same
	float m_imageSize;
	// X axis length to repeat the image
	int m_repeatX;
	// Y axis length to repeat the image
	int m_repeatY;
public:
	// Constructor of the filename, uses the one in RenderComponent
	RecurringRenderComponent(const wchar_t* filename);

	// Set image size
	void SetImageSize(float size);
	// Get image size
	float GetImageSize();

	// Set how many times the image should appear on the X axis
	void SetRepeatX(int amount);
	// Set how many times the image should appear on the Y axis
	void SetRepeatY(int amount);
	// Get how many times the image appears on the X axis
	int GetRepeatX();
	// Get how many times the image appears on the Y axis
	int GetRepeatY();

	// Override from RenderComponent draw the images into the grid system based on setvalues
	void Update(GameObject* pObject) override;
};