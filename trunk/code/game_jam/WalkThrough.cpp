#include "WalkThrough.h"
#include "Player.h"
#include <math.h>

WalkThrough::WalkThrough()
{
	SetSize({ 128, 66});
	SetPosition({ 500, 500 });
	SetRect(SGD::Rectangle( GetPos(),GetSize() ));
	m_eEnterSide = WL_RIGHT;
}


WalkThrough::~WalkThrough()
{
}

void WalkThrough::Update(float elapsedtime)
{
	SGD::Rectangle wallRect = GetRect();
	SGD::Rectangle otherRect = Player::GetInstance()->GetRect();

	if (!wallRect.IsIntersecting(otherRect))
	{
		return;
	}

	// Calculate difference in each edge
	float dLeft = abs(otherRect.left - wallRect.right);
	float dRight = abs(otherRect.right - wallRect.left);
	float dTop = abs(otherRect.top - wallRect.bottom);
	float dBottom = abs(otherRect.bottom - wallRect.top);

	// Collision with bottom of human
	if (dBottom == fmin(dLeft, fmin(dRight, fmin(dTop, dBottom))))
	{		
		if (m_eEnterSide == WL_BOTTOM || Player::GetInstance()->HasKey())
		{
			//float delta = wallRect.bottom - myRect.top;
			Player::GetInstance()->SetVelocity({ Player::GetInstance()->GetVelocity().x, 0.0f });
			Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y - dBottom });

			// No longer in the air
			Player::GetInstance()->SetIsInAir(false);
		}
	}
	// Collision with top of human
	else if (dTop == fmin(dRight, fmin(dTop, dLeft)))
	{
		
		if (m_eEnterSide == WL_TOP || Player::GetInstance()->HasKey())
		{
			//float delta = myRect.bottom - wallRect.top;
			//float delta = wallRect.bottom - myRect.top;
			Player::GetInstance()->SetVelocity({ Player::GetInstance()->GetVelocity().x, 0.0f });
			Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y + dTop });

			// No longer in the air
			Player::GetInstance()->SetIsInAir(false);
		}
	}
	// Collision with left of human
	else if (dLeft == fmin(dLeft, dRight))
	{
		if (m_eEnterSide == WL_RIGHT || Player::GetInstance()->HasKey())
		{
			//float delta = myRect.right - wallRect.left;
			//float delta = wallRect.bottom - myRect.top;
			Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
			Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x + dLeft, Player::GetInstance()->GetPos().y });

			// No longer in the air
			Player::GetInstance()->SetIsInAir(false);
		}
	}
	// Collision with right of human
	else
	{	
		if (m_eEnterSide == WL_LEFT || Player::GetInstance()->HasKey())
		{
			//float delta = wallRect.right - myRect.left;
			Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
			Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x - dRight, Player::GetInstance()->GetPos().y });

			// No longer in the air
			Player::GetInstance()->SetIsInAir(false);
		}
	}
}

void WalkThrough::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 0, 255, 255 });
}
