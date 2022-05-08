#pragma once
#include "RenderComponent.h"

class RecurringRenderComponent : public RenderComponent
{
private:
	float m_imageSize;
	int m_repeatX;
	int m_repeatY;
public:
	RecurringRenderComponent(const wchar_t* filename);

	void SetImageSize(float size);
	float GetImageSize();

	void SetRepeatX(int amount);
	void SetRepeatY(int amount);
	int GetRepeatX();
	int GetRepeatY();

	void Update(GameObject* pObject) override;
};