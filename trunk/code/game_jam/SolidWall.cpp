#include "SolidWall.h"
//FOR Testing
#include "Player.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

SolidWall::SolidWall()
{
	m_szSize = { 128, 128 };
	m_ptPosition = { 200, 500 };
	m_Rect = SGD::Rectangle(m_ptPosition, m_szSize);
}


SolidWall::~SolidWall()
{
}

void SolidWall::Update(float ElapsedTime)
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
		//Rigth Side of This
		if (rThis.right == rIntersection.right)
		{
			//SetPosition({ (float)rOther.left - GetSize().width + 1, GetPosition().y });
			Player::GetInstance()->SetPosition({ m_ptPosition.x + (m_szSize.width + 1), Player::GetInstance()->GetPos().y });
		}
		//Left Side of This
		if (rThis.left == rIntersection.left)
		{
			//SetPosition({ (float)rOther.right, GetPosition().y });
			Player::GetInstance()->SetPosition({ m_ptPosition.x - (Player::GetInstance()->GetSize().width + 1), Player::GetInstance()->GetPos().y });
		}
	}

	if (nIntersectWidth > nIntersectHeight)
	{
		//Top Side of This
		if (rThis.top == rIntersection.top)
		{
			//SetPosition({ GetPosition().x, (float)rObject.bottom });
			Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, m_ptPosition.y - (Player::GetInstance()->GetSize().height +1) });
			Player::GetInstance()->SetIsInAir(false);
			if (!Player::GetInstance()->IsJumping())
			{
				Player::GetInstance()->SetVelocity({ 0, 0 });
			}
			
		}
		//Bottom Side of This
		if (rThis.bottom == rIntersection.bottom)
		{
			//SetPosition({ GetPosition().x, (float)rObject.top - GetSize().height + 1 /*- nIntersectHeight*/ });
			//Player::GetInstance()->SetPosition({ m_ptPosition.x, (float)rOther.top - m_szSize.height + 1 /*- nIntersectHeight*/ });
		}		
	}
}

void SolidWall::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(m_ptPosition, m_szSize), { 255, 255, 0, 0 });
}