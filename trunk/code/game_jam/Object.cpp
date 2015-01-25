#include "Object.h"
#include <math.h>
#include "Player.h"

Object::Object()
{
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{

}

void Object::Render(void)
{

}

void Object::HandleCollision(Object * _object)
{
}

void Object::BasicCollision(Object * _other)
{	
	SGD::Rectangle myRect = GetRect();
	SGD::Rectangle otherRect = _other->GetRect();

	// Calculate difference in each edge
	float dLeft = abs(myRect.left - otherRect.right);
	float dRight = abs(myRect.right - otherRect.left);
	float dTop = abs(myRect.top - otherRect.bottom);
	float dBottom = abs(myRect.bottom - otherRect.top);

	// Collision with bottom of human
	if (dBottom == fmin(dLeft, fmin(dRight, fmin(dTop, dBottom))))
	{
		if (!GetClippedV())
		{
			SetVelocity({ m_vtVelocity.x, 5.0f });
			Move({ 0, -dBottom });

			// No longer in the air'
			SetIsInAir(false);		
			SetClippedV(true);
			Player::GetInstance()->SetPositive(!Player::GetInstance()->GetPositive());
	
			
		}
	}
	// Collision with top of human
	else if (dTop == fmin(dRight, fmin(dTop, dLeft)))
	{
		if (!GetClippedV())
		{
			SetVelocity({ m_vtVelocity.x, 0.0f });
			Move({ 0, dTop });

			// No longer in the air 
			//SetIsInAir(false);
			SetClippedV(true);
			Player::GetInstance()->SetPositive(!Player::GetInstance()->GetPositive());

		}
	}
	// Collision with left of human
	else if (dLeft == fmin(dLeft, dRight))
	{
		if (!GetClippedH())
		{
			SetVelocity({ 0.0f, m_vtVelocity.y });
			Move({ dLeft, 0 });

			// No longer in the air
			//SetIsInAir(false);
			SetClippedH(true);
		}
	}
	// Collision with right of human
	else
	{
		if (!GetClippedH())
		{
			SetVelocity({ 0.0f, m_vtVelocity.y });
			Move({ -dRight, 0 });

			// No longer in the air
			//SetIsInAir(false);
			SetClippedH(true);
		}
	}


}

void Object::Move(Vector _delta)
{
	m_ptPosition += _delta;
}