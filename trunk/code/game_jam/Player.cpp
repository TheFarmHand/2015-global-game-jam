#include "Player.h"
#include <iostream>
#include "Spring.h"
#include "WRAPPERS\SGD_InputManager.h"

#include "Data.h"
#include "Tiles.h"
#include <Windows.h>

Player::Player()
{
	SetImage(GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/PlaceHolder.jpg"));
	SetPosition({ 48, 400 });
	m_ptStartPosition = { 48, 400 };
	SetSize({ 64, 64 });
	SetVelocity({ 0.0f, 0.0f });
	m_fGravity = 1400.0f;
	SetIsInAir(true);
	m_bHasKey = false;
	m_fSpringTimer = 0.0f;
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
	m_rGOAL = SGD::Rectangle({64,608}, GetSize());
	m_bPassed = false;
}


Player::~Player()
{
}

void Player::Update(float elapsedTime)
{
	m_anANIM.Update(elapsedTime);
	m_anANIM.SetPos(GetPos());
	m_anANIM.SetSize(GetSize());
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

	//Input();

	

	if (GetInAir())
	{
		ApplyGravity(elapsedTime);
	}

	Point Temp = GetPos();
	Temp += GetVelocity() * elapsedTime;
	SetPosition(Temp);

	SetRect(SGD::Rectangle(GetPos(), GetSize()));

	SetIsInAir(true);
	SetClippedV(false);
	SetClippedH(false);
	SetDead(false);

	if (m_bHasKey)
	{
		GoalCollision();
	}
}

Player* Player::GetInstance(void)
{
	static Player s_Instance; //This is stored ONCE in global memory
	return &s_Instance;
}

void Player::Input(Tiles * _tiles)
{

	Data * data = Data::GetInstance();
	m_fGravity = data->levels[data->leveliter].gravity;
	if (data->levels[data->leveliter].input)
	{
		data->levels[data->leveliter].input(this);
		return;
	}

	if (InputManager::GetInstance()->IsKeyDown(Key::D) && SpaceFree({ 1.0f, -1.0f }, _tiles))
	{
		SetVelocity({ 300, GetVelocity().y });
		m_BLookingRight = true;
	}
	else if (InputManager::GetInstance()->IsKeyDown(Key::A) && SpaceFree({ -1.0f, -1.0f }, _tiles))
	{
		SetVelocity({ -300, GetVelocity().y });
		m_BLookingRight = false;
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
void Player::Jump()
{
	if (InputManager::GetInstance()->IsKeyPressed(Key::S) && !GetInAir())
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
}

void Player::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 0, 255, 0 });
	GraphicsManager::GetInstance()->DrawRectangle(m_rGOAL, { 255, 50, 255, 110 });
	if (GetVelocity().x != 0)
	{
		m_anANIM.Render(m_BLookingRight);
	}
	else
	{
		if (m_BLookingRight)
		{
			GraphicsManager::GetInstance()->DrawTextureSection(GetImage(), GetPos(), { Point(261, 127), Size(111, 124) }, {}, {}, {}, { .6f, .5f });
		}
		else
		{
			GraphicsManager::GetInstance()->DrawTextureSection(GetImage(), { (GetPos().x + GetSize().width), GetPos().y }, { Point(261, 127), Size(111, 124) }, {}, {}, {}, { -.6f, .5f });
		}
	}
	if (GetInAir())
	{
		if (m_BLookingRight)
		{
			GraphicsManager::GetInstance()->DrawTextureSection(GetImage(), GetPos(), { Point(374, 124), Size(111, 124) }, {}, {}, {}, { .6f, .5f });
		}
		else
		{
			GraphicsManager::GetInstance()->DrawTextureSection(GetImage(), { (GetPos().x + GetSize().width), GetPos().y }, { Point(374, 124), Size(111, 124) }, {}, {}, {}, { -.6f, .5f });
		}
	}
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
		SetDead(true);
	}
	// Falling blocks
	else if (_object->GetType() == OBJ_FallingBlock)
	{
		BasicCollision(_object);
	}
	else if (_object->GetType() == OBJ_Walkthrough)
	{
		
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


bool Player::SpaceFree(Vector _offset, Tiles * _tiles)
{
	// Temporary rect
	SGD::Rectangle rect = GetRect();
	rect.left += _offset.x;
	rect.right += _offset.x;
	rect.top += _offset.y;
	rect.bottom += _offset.y;

	// Determine the position of the enity in the array
	int x = (int)(rect.left / 32);
	int y = (int)(rect.top / 32);

	// Determine how far to check
	int width = (int)((rect.right - 1 - rect.left) / 32);
	int height = (int)((rect.bottom - 1 - rect.top) / 32);

	//int x2 = (int)((rect.right - 1) / 32);
	//int y2 = (int)((rect.bottom - 1) / 32);

	// loop through all adjacent collision pieces
	for (int xx = x; xx <= x + width + 1; ++xx)
	{
		for (int yy = y; yy <= y + height + 1; ++yy)
		{
			// Check if the current piece is in the bounds of the array
			if (xx >= 0 && xx < _tiles->GetWidth() && yy >= 0 && yy < _tiles->GetHeight())
			{
				// Figure out what is at this position
				int id = _tiles->GetCollisionLayer()[xx][yy];

				// If ID is no -1 check if rect collides with it
				if (id != -1)
				{
					SGD::Point point = { xx * 32.0f, yy * 32.0f };
					SGD::Size size = { 32, 32 };
					SGD::Rectangle rect2(point, size);
					return !rect2.IsIntersecting(rect);
				}
			}
		}
	}
	return true;
}

void Player::GoalCollision()
{

	RECT rMutant;
	rMutant.left = (LONG)GetRect().left;
	rMutant.top = (LONG)GetRect().top;
	rMutant.right = (LONG)GetRect().right;
	rMutant.bottom = (LONG)GetRect().bottom;

	RECT rObject;
	rObject.left = (LONG)m_rGOAL.left;
	rObject.top = (LONG)m_rGOAL.top;
	rObject.right = (LONG)m_rGOAL.right;
	rObject.bottom = (LONG)m_rGOAL.bottom;

	RECT rIntersection = {};

	IntersectRect(&rIntersection, &rObject, &rMutant);

	int nIntersectWidth = rIntersection.right - rIntersection.left;
	int nIntersectHeight = rIntersection.bottom - rIntersection.top;



	if (nIntersectHeight > nIntersectWidth)
	{
		m_bPassed = true;
		std::cout << "Passed\n";
	}

	if (nIntersectWidth > nIntersectHeight)
	{
		m_bPassed = true;
		std::cout << "Passed\n";
	}


}