#include "RecurringRenderComponent.h"
#include "GameObject.h"

/*
* Inherits from the RenderComponent, allows for the same image
* to be placed next to each other in a grid based system,
* currently used for placing the floor and walls
*
* @author W19023403
*/

// Set filename to initia image, uses base in RenderComponent
RecurringRenderComponent::RecurringRenderComponent(const wchar_t* filename) : RenderComponent(filename)
{
}

// Update called every frame to draw the images
void RecurringRenderComponent::Update(GameObject* pObject)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	for (int x = 0; x < GetRepeatX(); x++) // How many on the x axis
	{
		for (int y = 0; y < GetRepeatY(); y++) // How many on the y axis
		{
			Vector2D pos = pObject->GetPosition(); // Center position
			// Subtract depending on the X and Y axis values
			pos = pos + Vector2D(
				-(GetImageSize() * (GetRepeatX() * .5f)) + (GetImageSize() * (float)x) + (GetImageSize() * .5f), 
				-(GetImageSize() * (GetRepeatY() * .5f)) + (GetImageSize() * (float)y) + (GetImageSize() * .5f)
			);
			pDE->DrawAt(pos, image, 1.0f, pObject->GetAngle(), pObject->GetOpacity()); // Draw the image
		}
	}
};

// Set the image size
void RecurringRenderComponent::SetImageSize(float size)
{
	m_imageSize = size;
};
// Get the image size
float RecurringRenderComponent::GetImageSize()
{
	return m_imageSize;
};

// Set the amount of times the appear should appear on the X axis
void RecurringRenderComponent::SetRepeatX(int amount)
{
	m_repeatX = amount;
};
// Get the amount of times image appears on the X axis
int RecurringRenderComponent::GetRepeatX()
{
	return m_repeatX;
};

// Set the amount of times the appear should appear on the Y axis
void RecurringRenderComponent::SetRepeatY(int amount)
{
	m_repeatY = amount;
};
// Get the amount of times image appears on the XYaxis
int RecurringRenderComponent::GetRepeatY()
{
	return m_repeatY;
};