#include "FallingPlatform.h"
#include "Player.h"
#include <math.h>

FallingPlatform::FallingPlatform()
{
	SetSize({ 32, 32 });
	SetPosition({ 500, 500 });
	m_ptStartPosition = { 500, 500 };
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
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

}

void FallingPlatform::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 255, 0, 255 });
}



void FallingPlatform::HandleCollision(Object * _object)
{
	// Player
	if (_object->GetType() == OBJ_Player)
	{
		float TouchingTime = .5f;
		if (!m_bTouched)
		{
			m_bTouched = true;
			m_fTouchedCounter = TouchingTime;
		}
	}
}