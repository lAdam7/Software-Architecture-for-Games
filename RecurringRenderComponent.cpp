#include "RecurringRenderComponent.h"
#include "GameObject.h"

RecurringRenderComponent::RecurringRenderComponent(const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);
}

void RecurringRenderComponent::Update(GameObject* pObject)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	for (int x = 0; x < GetRepeatX(); x++)
	{
		for (int y = 0; y < GetRepeatY(); y++)
		{
			Vector2D pos = pObject->GetPosition();
			pos = pos + Vector2D(-(GetImageSize() * (GetRepeatX() * .5f)) + (GetImageSize() * (float)x) + (GetImageSize() * .5f), -(GetImageSize() * (GetRepeatY() * .5f)) + (GetImageSize() * (float)y) + (GetImageSize() * .5f));
			pDE->DrawAt(pos, image, 1.0f, pObject->GetAngle(), pObject->GetOpacity());
		}
	}
	/*
	for (int n = 0; n < GetRepeat(); n++)
	{
		Vector2D pos = pObject->GetPosition();
		if (IsHorizontal())
		{
			pos = pos + Vector2D(-(GetImageSize() * (GetRepeat() * .5)) + (GetImageSize() * n) + (GetImageSize()*.5), 0);
		}
		else
		{
			pos = pos + Vector2D(0, -(GetImageSize() * (GetRepeat() * .5)) + (GetImageSize() * n) + (GetImageSize() * .5));
		}
		
		pDE->DrawAt(pos, image, 1.0f, pObject->GetAngle(), pObject->GetOpacity());
	}*/
};

void RecurringRenderComponent::SetImageSize(float size)
{
	m_imageSize = size;
};
float RecurringRenderComponent::GetImageSize()
{
	return m_imageSize;
};

void RecurringRenderComponent::SetRepeatX(int amount)
{
	m_repeatX = amount;
};
int RecurringRenderComponent::GetRepeatX()
{
	return m_repeatX;
};

void RecurringRenderComponent::SetRepeatY(int amount)
{
	m_repeatY = amount;
};
int RecurringRenderComponent::GetRepeatY()
{
	return m_repeatY;
};