#include "RenderComponent.h"
#include "GameObject.h"

RenderComponent::RenderComponent(const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);
};

RenderComponent::~RenderComponent()
{

};

void RenderComponent::Update(GameObject* pObject)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	pDE->DrawAt(pObject->GetPosition(), image, 1.0f, pObject->GetAngle(), pObject->GetOpacity());
};

void RenderComponent::SetCurrentImage(int image)
{

};

void RenderComponent::AddImage(const wchar_t* filename)
{

};

void RenderComponent::AddImage(Animation* ani, const wchar_t* filename)
{

};