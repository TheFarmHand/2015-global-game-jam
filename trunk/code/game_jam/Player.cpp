#include "Player.h"
#include <iostream>
#include "Spring.h"
#include "WRAPPERS\SGD_InputManager.h"
#include "Data.h"

Player::Player()
{
	SetPosition({ 48, 400 });
	m_ptStartPosition = { 48, 400 };
	SetSize({ 64, 64 });
	SetVelocity({ 0.0f, 0.0f });
	m_fGravity = 1400.0f;
	SetIsInAir(true);
	m_bHasKey = false;
	m_fSpringTimer = 0.0f;
	SetRect(Rectangle(GetPos(), GetSize()));
}


Player::~Player()
{
}

void Player::Update(float elapsedTime)
{
	if (m_fSpringTimer > 0.0f)
	{
		m_fSpringTimer -= elapsedTime;
	}


	Data * data = Data::GetInstance();

	if (data->levels[data->leveliter].update)
	{
		data->levels[data->leveliter].update(elapsedTime);
		return;
	}
	Input();

	

	if (GetInAir())
	{
		ApplyGravity(elapsedTime);
	}

	if (m_fJumpCount > 0)
	{
		m_fJumpCount -= elapsedTime;
	}
	else
	{
		m_fJumpCount = .1f;
		std::cout << GetInAir() << "\n";
	}
	Point Temp = GetPos();
	Temp += GetVelocity() * elapsedTime;
	SetPosition(Temp);

	SetRect(Rectangle(GetPos(), GetSize()));

	SetIsInAir(true);
	SetClippedV(false);
	SetClippedH(false);
}

Player* Player::GetInstance(void)
{
	static Player s_Instance; //This is stored ONCE in global memory
	return &s_Instance;
}

void Player::Input()
{
	Data * data = Data::GetInstance();

	if (data->levels[data->leveliter].input)
	{
		data->levels[data->leveliter].input();
		return;
	}

	if (InputManager::GetInstance()->IsKeyDown(Key::D))
	{
		SetVelocity({ 300, GetVelocity().y });
	}
	else if (InputManager::GetInstance()->IsKeyDown(Key::A))
	{
		SetVelocity({ -300, GetVelocity().y });
	}
	else if (m_fSpringTimer <= 0.0f)
	{
		SetVelocity({ 0, GetVelocity().y });
	}

	if (InputManager::GetInstance()->IsKeyPressed(Key::Space) && !GetInAir())
	{
		SetVelocity({ GetVelocity().x, -800 });
		SetIsInAir(true);
		m_bJumping = true;
		m_fJumpCount = .5f;
	}
}

void Player::ApplyGravity(float _dt)
{
	SetVelocity({ GetVelocity().x, GetVelocity().y + m_fGravity * _dt });
	//if (!m_bJumping)
	//{
	//	m_vtVelocity.y = 0;
	//}
}

void Player::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 0, 255, 0 });
}


void Player::HandleCollision(Object * _object)
{
	// Solid wall
	if (_object->GetType() == OBJ_SolidWall)
	{
		BasicCollision(_object);	
	}
	// Death touch
	else if (_object->GetType() == OBJ_DeathTouch)
	{
		SetPosition(m_ptStartPosition);
	}
	// Falling blocks
	else if (_object->GetType() == OBJ_FallingBlock)
	{
		BasicCollision(_object);
	}
	else if (_object->GetType() == OBJ_Walkthrough)
	{
		BasicCollision(_object);
	}
	// Springs
	else if (_object->GetType() == OBJ_Spring)
	{
		Spring * spring = dynamic_cast<Spring*>(_object);
		BasicCollision(_object);
		m_fSpringTimer = 0.5f;
		switch (spring->GetDirection())
		{
			// Facing right
			case 0:
			{
				SetVelocity({spring->GetPower(), GetVelocity().y });
				break;
			}
			// Facing down
			case 1:
			{
				SetVelocity({ GetVelocity().x, spring->GetPower() });
				break;
			}
			// Facing left
			case 2:
			{
				SetVelocity({ -spring->GetPower(), GetVelocity().y });
				break;
			}
			// Facing up
			case 3:
			{
				SetVelocity({ GetVelocity().x, -spring->GetPower() });
				break;
			}
		}
	}
}