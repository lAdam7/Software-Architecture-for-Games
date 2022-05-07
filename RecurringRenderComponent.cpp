#include "RecurringRenderComponent.h"
#include "GameObject.h";

RecurringRenderComponent::RecurringRenderComponent()
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(L"concrete.png");
}

void RecurringRenderComponent::Update(GameObject* pObject)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
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
	}
};

void RecurringRenderComponent::SetImageSize(float size)
{
	m_imageSize = size;
};
float RecurringRenderComponent::GetImageSize()
{
	return m_imageSize;
};

void RecurringRenderComponent::SetHorizontal(bool horizontal)
{
	m_horizontal = horizontal;
};
bool RecurringRenderComponent::IsHorizontal()
{
	return m_horizontal;
};

void RecurringRenderComponent::SetRepeat(int amount)
{
	m_repeat = amount;
};
int RecurringRenderComponent::GetRepeat()
{
	return m_repeat;
};