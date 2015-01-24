#include "DeathTouch.h"
//FOR Testign
#include "Player.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

DeathTouch::DeathTouch()
{
	m_szSize = { 64, 64 };
	m_ptPosition = { 500, 500 };
	m_Rect = SGD::Rectangle(m_ptPosition, m_szSize);
}


DeathTouch::~DeathTouch()
{

}

void DeathTouch::Update(float ElapsedTime)
{
	RECT rThis;
	rThis.left = (LONG)GetRect().left;
	rThis.top = (LONG)GetRect().top;
	rThis.right = (LONG)GetRect().right;
	rThis.bottom = (LONG)GetRect().bottom;

	RECT rOther;
	rOther.left = (LONG)Player::GetInstance()->GetRect().left;
	rOther.top = (LONG)Player::GetInstance()->GetRect().top;
	rOther.right = (LONG)Player::GetInstance()->GetRect().right;
	rOther.bottom = (LONG)Player::GetInstance()->GetRect().bottom;

	RECT rIntersection = {};

	IntersectRect(&rIntersection, &rOther, &rThis);

	int nIntersectWidth = rIntersection.right - rIntersection.left;
	int nIntersectHeight = rIntersection.bottom - rIntersection.top;



	if (nIntersectHeight > nIntersectWidth)
	{
		if (rThis.right == rIntersection.right)
		{
			//SetPosition({ (float)rOther.left - GetSize().width + 1, GetPosition().y });
			Player::GetInstance()->SetPosition(Player::GetInstance()->GetStartPos());
		}
		if (rThis.left == rIntersection.left)
		{
			//SetPosition({ (float)rOther.right, GetPosition().y });
			Player::GetInstance()->SetPosition(Player::GetInstance()->GetStartPos());
		}
	}

	if (nIntersectWidth > nIntersectHeight)
	{
		if (rThis.bottom == rIntersection.bottom)
		{
			//SetPosition({ GetPosition().x, (float)rObject.top - GetSize().height + 1 /*- nIntersectHeight*/ });
			Player::GetInstance()->SetPosition(Player::GetInstance()->GetStartPos());
		}
		if (rThis.top == rIntersection.top)
		{
			//SetPosition({ GetPosition().x, (float)rObject.bottom });
			Player::GetInstance()->SetPosition(Player::GetInstance()->GetStartPos());
		}
	}
}

void DeathTouch::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(m_ptPosition, m_szSize), { 255, 255, 0, 0 });
}