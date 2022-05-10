#include "RenderComponent.h"
#include "GameObject.h"

/*
* Base RenderComponent, stores the image
* of each object, and renders on every frame
* its called
*
* @author W19023403
*/

// Constructor, load the image
RenderComponent::RenderComponent(const wchar_t* filename)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(filename);
};
// Destructor
RenderComponent::~RenderComponent()
{

};

// Used over in the animation component
void RenderComponent::AddImage(const wchar_t* filename) {};
void RenderComponent::AddImage(Animation* ani, const wchar_t* filename) {};
void RenderComponent::SetCurrentImage(int image) {};

// Called every frame draw the image
void RenderComponent::Update(GameObject* pObject)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	pDE->DrawAt(pObject->GetPosition(), image, 1.0f, pObject->GetAngle(), pObject->GetOpacity());
};