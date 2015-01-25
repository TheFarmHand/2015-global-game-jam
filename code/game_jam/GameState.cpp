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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//For Testing
static FallingPlatform fp;
//static Spring TheSpring;
//static LKey TheKey;
//static Spring TheSpring2;

void altInput(Player *_player)
{

	if (InputManager::GetInstance()->IsKeyDown(Key::A))
	{
		_player->SetVelocity({ 300, _player->GetVelocity().y });
	}
	else if (InputManager::GetInstance()->IsKeyDown(Key::D))
	{
		_player->SetVelocity({ -300, _player->GetVelocity().y });
	}
	else if (_player->GetJumpTimer() <= 0.0f)
	{
		_player->SetVelocity({ 0, _player->GetVelocity().y });
	}

	_player->Jump();
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
	delete walkThrough1;
	delete walkThrough2;
	delete key;
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

	// End of loop
	}
	return playing;
}


void GameState::Render()
{
	//TheSpring.Render();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	//TheSpring2.Render();
	fp.Render();
	//TheKey.Render();
	Player::GetInstance()->Render();
	spring1->Render();
	spring2->Render();
	spring3->Render();
	platform->Render();
	/*walkThrough1->Render();
	walkThrough2->Render();*/
	key->Render();
	m_pLevel->Render();


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
}


void GameState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::W) || input->IsKeyPressed(SGD::Key::UpArrow)) // Menu up
		cursor -= 1;
	else if (input->IsKeyPressed(SGD::Key::S) || input->IsKeyPressed(SGD::Key::DownArrow)) // Menu down
		cursor += 1;

	if (input->IsKeyPressed(SGD::Key::Escape))
		paused = true;

	if (input->IsKeyPressed(SGD::Key::Enter)) // Select
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
	//TheKey.SetPosition(TheKey.GetStartPos());
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
	spring3->SetPosition({ 544, 224 });
	spring3->SetDirection(0);
	spring3->SetRect({ spring3->GetPos(), spring3->GetSize() });

	// Platforms
	platform = new FallingPlatform();
	platform->SetPosition({ 704, 448 });
	platform->SetSize({ 64, 32 });
	platform->SetStartPosition(platform->GetPos());
	platform->SetRect({ platform->GetPos(), platform->GetSize() });

	// Walkthrough walls
	walkThrough1 = new WalkThrough;
	walkThrough1->SetPosition({ 32, 256 });
	walkThrough1->SetSize({ 128, 32 });
	walkThrough1->SetEnter(WalkThroughEnter::WL_TOP);
	walkThrough1->SetRect({ walkThrough1->GetPos(), walkThrough1->GetSize() });

	walkThrough2 = new WalkThrough;
	walkThrough2->SetPosition({ 160, 384 });
	walkThrough2->SetSize({ 32, 96 });
	walkThrough1->SetEnter(WalkThroughEnter::WL_LEFT);
	walkThrough2->SetRect({ walkThrough2->GetPos(), walkThrough2->GetSize() });

	// Key
	key = new LKey();
	key->SetPosition({ 896, 352 });
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

	// walkThrough1
	if (Player::GetInstance()->GetRect().IsIntersecting(walkThrough1->GetRect()))
	{
		Player::GetInstance()->HandleCollision(walkThrough1);
		walkThrough1->HandleCollision(Player::GetInstance());
	}

	// walkThrough2
	if (Player::GetInstance()->GetRect().IsIntersecting(walkThrough2->GetRect()))
	{
		Player::GetInstance()->HandleCollision(walkThrough2);
		walkThrough2->HandleCollision(Player::GetInstance());
	}

	// key
	if (Player::GetInstance()->GetRect().IsIntersecting(key->GetRect()))
	{
		Player::GetInstance()->HandleCollision(key);
		key->HandleCollision(Player::GetInstance());
	}
}