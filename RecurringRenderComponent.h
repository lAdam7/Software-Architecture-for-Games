#pragma once
#include "RenderComponent.h"

class RecurringRenderComponent : public RenderComponent
{
private:
	float m_imageSize;
	bool m_horizontal;
	int m_repeat;
public:
	RecurringRenderComponent();

	void SetImageSize(float size);
	float GetImageSize();

	void SetHorizontal(bool horizontal);
	bool IsHorizontal();

	void SetRepeat(int amount);
	int GetRepeat();

	void Update(GameObject* pObject) override;
};