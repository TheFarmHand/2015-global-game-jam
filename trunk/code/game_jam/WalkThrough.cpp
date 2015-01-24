#include "WalkThrough.h"
#include "Player.h"
#include <math.h>

WalkThrough::WalkThrough()
{
	SetSize({ 128, 66});
	SetPosition({ 300, 400 });
	SetRect(SGD::Rectangle( GetPos(),GetSize() ));
	
	m_eBlockSide = WL_TOP;
}


WalkThrough::~WalkThrough()
{
}

void WalkThrough::Update(float elapsedtime)
{
	//Handle Collision
	if (Player::GetInstance()->HasKey()) return;

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
		if (m_eBlockSide == WL_TOP || Player::GetInstance()->HasKey())
		{
			//float delta = wallRect.bottom - myRect.top;
			Player::GetInstance()->SetVelocity({ Player::GetInstance()->GetVelocity().x, 5.0f });
			float y = Player::GetInstance()->GetPos().y;
			if (y < (GetPos().y)+50)
			{
				Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y - dBottom });
			}

			// No longer in the air
			Player::GetInstance()->SetIsInAir(false);
		}
	}
	// Collision with top of human
	else if (dTop == fmin(dRight, fmin(dTop, dLeft)))
	{
		
		if (m_eBlockSide == WL_BOTTOM || Player::GetInstance()->HasKey())
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
		if (m_eBlockSide == WL_RIGHT || Player::GetInstance()->HasKey())
		{
			//float delta = myRect.right - wallRect.left;
			//float delta = wallRect.bottom - myRect.top;
			Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
			if (Player::GetInstance()->GetPos().x > ((GetPos().x + GetSize().width) - 10))
			{
				Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x + dLeft, Player::GetInstance()->GetPos().y });
			}
			
			
			// No longer in the air
			Player::GetInstance()->SetIsInAir(false);
		}
	}
	// Collision with right of human
	else
	{	
		if (m_eBlockSide == WL_LEFT || Player::GetInstance()->HasKey())
		{
			//float delta = wallRect.right - myRect.left;
			Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
			if ((Player::GetInstance()->GetPos().x + Player::GetInstance()->GetSize().width) < (GetPos().x) + 10)
			{
				Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x - dRight, Player::GetInstance()->GetPos().y });
			}

			// No longer in the air
			Player::GetInstance()->SetIsInAir(false);
		}
	}
}

void WalkThrough::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 0, 255, 255 });
}
