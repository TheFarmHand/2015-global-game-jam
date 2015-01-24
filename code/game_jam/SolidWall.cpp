#include "SolidWall.h"
//FOR Testing
#include "Player.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <math.h>

SolidWall::SolidWall()
{
	SetSize({ 128, 128 });
	SetPosition({ 200, 500 });
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
	SetType(OBJ_SolidWall);
}


SolidWall::~SolidWall()
{
}

void SolidWall::Update(float ElapsedTime)
{
	SGD::Rectangle wallRect = GetRect();
	SGD::Rectangle otherRect = Player::GetInstance()->GetRect();

	if (!wallRect.IsIntersecting(otherRect))
	{
		return;
	}

	//RECT rThis;
	//rThis.left = (LONG)GetRect().left;
	//rThis.top = (LONG)GetRect().top;
	//rThis.right = (LONG)GetRect().right;
	//rThis.bottom = (LONG)GetRect().bottom;

	//RECT rOther;
	//rOther.left = (LONG)Player::GetInstance()->GetRect().left;
	//rOther.top = (LONG)Player::GetInstance()->GetRect().top;
	//rOther.right = (LONG)Player::GetInstance()->GetRect().right;
	//rOther.bottom = (LONG)Player::GetInstance()->GetRect().bottom;

	//RECT rIntersection = {};

	//IntersectRect(&rIntersection, &rOther, &rThis);

	//int nIntersectWidth = rIntersection.right - rIntersection.left;
	//int nIntersectHeight = rIntersection.bottom - rIntersection.top;
	
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
	}
	// Collision with right of human
	else
	{
		//float delta = wallRect.right - myRect.left;
		Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
		Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x - dRight, Player::GetInstance()->GetPos().y });

		// No longer in the air
		Player::GetInstance()->SetIsInAir(false);
	}


	//if (nIntersectHeight > nIntersectWidth)
	//{
	//	//Rigth Side of This
	//	if (rThis.right == rIntersection.right)
	//	{
	//		//SetPosition({ (float)rOther.left - GetSize().width + 1, GetPosition().y });
	//		Player::GetInstance()->SetPosition({ m_ptPosition.x + (m_szSize.width + 1), Player::GetInstance()->GetPos().y });
	//	}
	//	//Left Side of This
	//	if (rThis.left == rIntersection.left)
	//	{
	//		//SetPosition({ (float)rOther.right, GetPosition().y });
	//		Player::GetInstance()->SetPosition({ m_ptPosition.x - (Player::GetInstance()->GetSize().width + 1), Player::GetInstance()->GetPos().y });
	//	}
	//}

	//if (nIntersectWidth > nIntersectHeight)
	//{
	//	//Top Side of This
	//	if (rThis.top == rIntersection.top)
	//	{
	//		//SetPosition({ GetPosition().x, (float)rObject.bottom });
	//		Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, m_ptPosition.y - (Player::GetInstance()->GetSize().height +1) });
	//		Player::GetInstance()->SetIsInAir(false);
	//		if (!Player::GetInstance()->IsJumping())
	//		{
	//			Player::GetInstance()->SetVelocity({ 0, 0 });
	//		}
	//		
	//	}
	//	//Bottom Side of This
	//	if (rThis.bottom == rIntersection.bottom)
	//	{
	//		//SetPosition({ GetPosition().x, (float)rObject.top - GetSize().height + 1 /*- nIntersectHeight*/ });
	//		//Player::GetInstance()->SetPosition({ m_ptPosition.x, (float)rOther.top - m_szSize.height + 1 /*- nIntersectHeight*/ });
	//	}		
	//}
}

void SolidWall::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 255, 0, 0 });
}