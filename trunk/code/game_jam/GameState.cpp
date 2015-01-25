#include "GameState.h"
#include "Tiles.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Level.h"
#include "FallingPlatform.h"
#include "WalkThrough.h"
#include "Spring.h"
#include "Key.h"
#include "Spring.h"
#include "Data.h"
#include "BitmapFont.h"
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static BitmapFont *FONT;
//For Testing





void altInput(Player *_player, Tiles * _tiles)
{

	
	

	if (InputManager::GetInstance()->IsKeyDown(Key::A) && _player->SpaceFree({ 1.0f, -1.0f }, _tiles))
	{
		_player->SetVelocity({ 300, _player->GetVelocity().y });
		_player->SetLookingRight(true);
	}
	else if (InputManager::GetInstance()->IsKeyDown(Key::D) && _player->SpaceFree({ -1.0f, -1.0f }, _tiles))
	{
		_player->SetVelocity({ -300, _player->GetVelocity().y });
		_player->SetLookingRight(false);

	}
	else if (_player->GetJumpTimer() <= 0.0f)
	{
		_player->SetVelocity({ 0, _player->GetVelocity().y });
	}

	_player->Jump();
	/*FONT = new BitmapFont;
	FONT->Initialize("Assets/Font.fnt");*/
}

GameState::GameState()
{
	m_pLevel = new Level();
	m_pObjManager = new ObjectManager();
	font = new BitmapFont;
	font->Initialize("Assets/Font.fnt");

	// Initialize and setup all obstacles
	CreateObstacles();

	//defining levels
	Data::GetInstance()->levels[1].gravity = 700.0f;
	Data::GetInstance()->levels[2].input = altInput;

	// Load in each image
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	m_tBackgrounds[0] = pGraphics->LoadTexture("Assets/graphics/Background1.png");
	m_tBackgrounds[1] = pGraphics->LoadTexture("Assets/graphics/Background2.png");
	m_tBackgrounds[2] = pGraphics->LoadTexture("Assets/graphics/Background3.png");
	m_tBackgrounds[3] = pGraphics->LoadTexture("Assets/graphics/Background4.png");
	m_tBackgrounds[4] = pGraphics->LoadTexture("Assets/graphics/Background5.png");
	//m_tBackgrounds[5] = pGraphics->LoadTexture("Assets/graphics/Background6.png");
	m_tBackgrounds[6] = pGraphics->LoadTexture("Assets/graphics/Background7.png");
	m_tBackgrounds[7] = pGraphics->LoadTexture("Assets/graphics/Background8.png");
	m_tBackgrounds[8] = pGraphics->LoadTexture("Assets/graphics/Background9.png");
	m_tBackgrounds[9] = pGraphics->LoadTexture("Assets/graphics/Background10.png");
	m_tBackgrounds[10] = pGraphics->LoadTexture("Assets/graphics/Background11.png");

}


GameState::~GameState()
{
	delete m_pLevel;
	m_pObjManager->ClearAndDeleteAll();
	delete m_pObjManager;

	font->Terminate();
	delete font;

	// Delete obstacles
	delete spring1;
	delete spring2;
	delete spring3;
	delete platform;
	delete key;
	delete FONT;

	// Release each background
	for (unsigned int i = 0; i < 11; ++i)
	{
		if (i != 5)
		{
			// release the texture
			SGD::GraphicsManager::GetInstance()->UnloadTexture(m_tBackgrounds[i]);
		}
	}
}

int GameState::Update(float dt)
{

	if (!paused) // Make sure all gameplay code is inside here, otherwise pause won't work
	{	

		Player::GetInstance()->Update(dt);

	// Update each obstacles
	spring1->Update(dt);
	spring2->Update(dt);
	spring3->Update(dt);
	platform->Update(dt);
	/*walkThrough1->Update(dt);
	walkThrough2->Update(dt);*/
	key->Update(dt);
	
		m_pLevel->Update(dt);

		// Check collisions
		CheckObstacleCollisions();

		// Player world collision
		m_pLevel->GetTiles()->CheckCollision(Player::GetInstance());

		Player::GetInstance()->Input(m_pLevel->GetTiles());

		if (Player::GetInstance()->GetDead())
		{
			ResetLevel();
		}

		// End of loop
	}
	return playing;
}

void GameState::NextLevel()
{
	Data::GetInstance()->leveliter++;
	ResetLevel();
}

void GameState::Render()
{
	//TheSpring.Render();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();

	// Draw background first
	if (Data::GetInstance()->leveliter != 5)
	{
		graphics->DrawTexture(m_tBackgrounds[Data::GetInstance()->leveliter], { 0.0f, 0.0f }, 0.0f, { 0.0f, 0.0f }, { 255, 255, 255 }, { 1.0f, 1.0f });
	}

	Player::GetInstance()->Render();
	spring1->Render();
	spring2->Render();
	spring3->Render();
	platform->Render();
	key->Render();
	m_pLevel->Render();

	std::ostringstream info;
	info << "Level " << Data::GetInstance()->leveliter + 1 << ":  " << Data::GetInstance()->levels[Data::GetInstance()->leveliter].hint;

	font->Draw(info.str().c_str(), { 5.0f, 0.0f }, 1.0f, {0,0,0 });
	#pragma region Pause Menu

	if (paused == true)
	{
		font->Draw("Paused", { 512 - font->Center("Paused"), 100 }, 1, { 255, 255, 255 });
		font->Draw("~~~~~~", { 512 - font->Center("~~~~~~"), 120 }, 1, { 255, 255, 255 });

		if (cursor == 0)
			font->Draw("Resume", { 512 - font->Center("Resume"), 300 }, 1, { 0, 255, 255 }); // Resume selected
		else					    
			font->Draw("Resume", { 512 - font->Center("Resume"), 300 }, 1, { 255, 255, 255 }); // Resume unselected

		if (cursor == 1)
			font->Draw("Exit", { 512 - font->Center("Exit"), 350 }, 1, { 0, 255, 255 }); // Exit selected
		else
			font->Draw("Exit", { 512 - font->Center("Exit"), 350 }, 1, { 255, 255, 255 }); // Exit unselected 
	}
	
#pragma endregion
	//font->Draw("asd;fjkllllasdfljk;;klasd;jklasdf", { 0, -50 }, 50, { 255, 0, 0 });
	//font->Draw("asdfjkl;asd;fjklasd;fjkl;jklasdfasd;fjklasd;fjklasd;fjklasd;fjklasd;fjklasd;fjklasfasdf;jklasd;fjklasd;fjklasd;fjklad;fjkl;jklasd;jklasdf;jklasdf;jkljkl;asdf;jklasdfss", { 0, 0 }, 50, { 255, 0, 0 });
}


void GameState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::W) || input->IsKeyPressed(SGD::Key::UpArrow) || input->GetLeftJoystick(0).y == 1) // Menu up
		cursor -= 1;
	else if (input->IsKeyPressed(SGD::Key::S) || input->IsKeyPressed(SGD::Key::DownArrow) || input->GetLeftJoystick(0).y == -1) // Menu down
		cursor += 1;

	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 7))
		paused = true;

	if (input->IsKeyPressed(SGD::Key::Enter) || input->IsButtonPressed(0, 7)) // Select
	{
		if (cursor == 0)
			paused = true;
		else if (cursor == 1)
			playing = 1;

	}

	if (cursor < 0)
		cursor = 1;
	else if (cursor > 1)
		cursor = 0;

	if (input->IsKeyDown(SGD::Key::R))
	{
		ResetLevel();
	}
}

void GameState::ResetLevel()
{
	Player::GetInstance()->SetPosition(Player::GetInstance()->GetStartPos());
	Player::GetInstance()->SetHasKey(false);
	key->SetPosition(key->GetStartPos()); 
}

void GameState::CreateObstacles()
{
	// Springs
	spring1 = new Spring();
	spring1->SetPosition({ 416, 672 });
	spring1->SetDirection(3);
	spring1->SetRect({ spring1->GetPos(), spring1->GetSize() });

	spring2 = new Spring();
	spring2->SetPosition({ 416, 32 });
	spring2->SetDirection(1);
	spring2->SetRect({ spring2->GetPos(), spring2->GetSize() });

	spring3 = new Spring();
	spring3->SetPosition({ 608, 224 });
	spring3->SetDirection(0);
	spring3->SetRect({ spring3->GetPos(), spring3->GetSize() });

	// Platforms
	platform = new FallingPlatform();
	platform->SetPosition({ 896, 352 });
	platform->SetSize({ 64, 32 });
	platform->SetStartPosition(platform->GetPos());
	platform->SetRect({ platform->GetPos(), platform->GetSize() });

	// Key
	key = new LKey();
	key->SetPosition({ 1216, 512 });
	key->SetStartPos(key->GetPos());
	key->SetSize({ 32, 32 });
	key->SetRect({ key->GetPos(), key->GetSize() });

}

void GameState::CheckObstacleCollisions()
{
	// Spring 1
	if (Player::GetInstance()->GetRect().IsIntersecting(spring1->GetRect()))
	{
		Player::GetInstance()->HandleCollision(spring1);
		spring1->HandleCollision(Player::GetInstance());
	}

	// Spring 2
	if (Player::GetInstance()->GetRect().IsIntersecting(spring2->GetRect()))
	{
		Player::GetInstance()->HandleCollision(spring2);
		spring2->HandleCollision(Player::GetInstance());
	}

	// Spring 3
	if (Player::GetInstance()->GetRect().IsIntersecting(spring3->GetRect()))
	{
		Player::GetInstance()->HandleCollision(spring3);
		spring3->HandleCollision(Player::GetInstance());
	}

	// Platform
	if (Player::GetInstance()->GetRect().IsIntersecting(platform->GetRect()))
	{
		Player::GetInstance()->HandleCollision(platform);
		platform->HandleCollision(Player::GetInstance());
	}

	// key
	if (Player::GetInstance()->GetRect().IsIntersecting(key->GetRect()))
	{
		Player::GetInstance()->HandleCollision(key);
		key->HandleCollision(Player::GetInstance());
	}
}