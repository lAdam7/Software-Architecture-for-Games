#include "BulletPhysicsComponent.h"

void BulletPhysicsComponent::Update(HUD* pHUD, GameObject* pObject, float frameTime)
{
	pObject->SetPosition(pObject->GetPosition() + velocity * frameTime);
	/*
	float magnitude = 50000.0f;
	Vector2D rot;
	rot.setBearing(velocity.angle(), magnitude);
	
	Segment2D intersectLine;
	intersectLine.PlaceAt(pObject->GetPosition(), pObject->GetPosition() + rot);

	MyDrawEngine::GetInstance()->DrawLine(pObject->GetPosition(), pObject->GetPosition() + rot, MyDrawEngine::RED);
	*/
	//m_timer = m_timer - frameTime;
	if (m_timer < 0)
	{
		pObject->DeleteObject();
	}
};

/*
* EnemyPhysicsComponent* pEnemyPhysics = dynamic_cast<EnemyPhysicsComponent*>(pObject->GetPhysicsComponent());

		// Check if enemy is currently chasing player, if not then enemy isn't in a viewable range
		
		float magnitude = (pObject->GetPosition() - message.pSource->GetPosition()).magnitude() * 2;

		Vector2D angle;
		angle.setBearing(message.pSource->GetAngle(), magnitude);

		Segment2D intersectLine;
		intersectLine.PlaceAt(message.pSource->GetPosition(), message.pSource->GetPosition() + angle);

		if (pObject->GetCollisionComponent()->GetShape(pObject).Intersects(intersectLine))
		{
			throw "IM HIT";
		}
*/