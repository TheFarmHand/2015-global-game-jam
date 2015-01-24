#include "FallingPlatform.h"
#include "Player.h"
#include <math.h>

FallingPlatform::FallingPlatform()
{
	SetSize({ 64, 64 });
	SetPosition({ 500, 500 });
	m_ptStartPosition = { 500, 500 };
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
	SetType(OBJ_FallingBlock);
}


FallingPlatform::~FallingPlatform()
{
}

void FallingPlatform::Update(float ElapsedTime)
{
	//Falling Platfrom Functionality
	float TouchingTime = .5f;
	if (m_bTouched)
	{
		m_fTouchedCounter -= ElapsedTime;
	}

	if (m_fTouchedCounter < 0)
	{
		m_vtVelocity.y = 200;
	}

	if (m_fTouchedCounter < -1)
	{
		m_bTouched = false;
		SetPosition(m_ptStartPosition);
		m_vtVelocity = {};
		m_fTouchedCounter = 0;
	}

	Point Temp = GetPos();
	Temp += m_vtVelocity * ElapsedTime;
	SetPosition(Temp);
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
	//Collision
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
		//float delta = wallRect.bottom - myRect.top;
		Player::GetInstance()->SetVelocity({ Player::GetInstance()->GetVelocity().x, 0.0f });
		Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y - dBottom });

		// No longer in the air
		Player::GetInstance()->SetIsInAir(false);
		if (!m_bTouched)
		{
			m_fTouchedCounter = TouchingTime;
		}
		m_bTouched = true;
	}
	// Collision with top of human
	else if (dTop == fmin(dRight, fmin(dTop, dLeft)))
	{
		//float delta = myRect.bottom - wallRect.top;
		//float delta = wallRect.bottom - myRect.top;
		Player::GetInstance()->SetVelocity({ Player::GetInstance()->GetVelocity().x, 0.0f });
		Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y + dTop });

		// No longer in the air
		Player::GetInstance()->SetIsInAir(false);
		if (!m_bTouched)
		{
			m_fTouchedCounter = TouchingTime;
		}
		m_bTouched = true;
	}
	// Collision with left of human
	else if (dLeft == fmin(dLeft, dRight))
	{
		//float delta = myRect.right - wallRect.left;
		//float delta = wallRect.bottom - myRect.top;
		Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
		Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x + dLeft, Player::GetInstance()->GetPos().y });

		// No longer in the air
		Player::GetInstance()->SetIsInAir(false);
		if (!m_bTouched)
		{
			m_fTouchedCounter = TouchingTime;
		}
		m_bTouched = true;
	}
	// Collision with right of human
	else
	{
		//float delta = wallRect.right - myRect.left;
		Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
		Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x - dRight, Player::GetInstance()->GetPos().y });

		// No longer in the air
		Player::GetInstance()->SetIsInAir(false);
		if (!m_bTouched)
		{
			m_fTouchedCounter = TouchingTime;
		}
		m_bTouched = true;
	}
}

void FallingPlatform::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 255, 0, 255 });
}