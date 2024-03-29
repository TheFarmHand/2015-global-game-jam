#include "GameState.h"
#include "Tiles.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
#include "WRAPPERS\SGD_AudioManager.h"
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


void TrippyRender(GameState * _gamestate)
{
	_gamestate->AltRender();
}

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

void teleport(Player * _player, Tiles * _tiles)
{
	InputManager * input = InputManager::GetInstance();



	if (input->IsKeyDown(SGD::Key::One) && Data::GetInstance()->teles[0])
	{
		_player->SetPosition({240.0f,410.0f});
		Data::GetInstance()->teles[0] = false;
	}
	else if (input->IsKeyDown(SGD::Key::Two) && Data::GetInstance()->teles[1])
	{
		_player->SetPosition({220.0f,185.0f});
		Data::GetInstance()->teles[1] = false;
	}
	else if (input->IsKeyDown(SGD::Key::Three) && Data::GetInstance()->teles[2])
	{
		_player->SetPosition({1210.0f,500.0f});
		Data::GetInstance()->teles[2] = false;
	}
	else if (input->IsKeyDown(SGD::Key::Four) && Data::GetInstance()->teles[3])
	{
		_player->SetPosition({605.0f,415.0f});
		Data::GetInstance()->teles[3] = false;
	}
	else if (input->IsKeyDown(SGD::Key::Five) && Data::GetInstance()->teles[4])
	{
		_player->SetPosition({48.0f,608.0f});
		Data::GetInstance()->teles[4] = false;
	}
}

void collision(Player * _player, Object * _object)
{
	_player->OtherCollsision(_object);
}
GameState::GameState()
{
	m_fFade = 0.0f;
	m_fFadeTimer = 0.0f;
	m_fQuoteTimer = 2.0f;
	m_pLevel = new Level();
	m_pObjManager = new ObjectManager();
	font = new BitmapFont;
	font->Initialize("Assets/Font.fnt");

	// Initialize and setup all obstacles
	CreateObstacles();


	// Level hints
	Data::GetInstance()->levels[0].hint = "           Welcome!           ";
	Data::GetInstance()->levels[1].hint = "     Welcome to the moon!     ";
	Data::GetInstance()->levels[2].hint = "         Opposite day         ";
	Data::GetInstance()->levels[3].hint = "          1,2,3,4,5           ";
	Data::GetInstance()->levels[4].hint = "            2 + 3             ";
	Data::GetInstance()->levels[5].hint = "          Remember?           ";
	Data::GetInstance()->levels[6].hint = "          Inception            ";
	Data::GetInstance()->levels[7].hint = "I don't think that was candy...";
	Data::GetInstance()->levels[8].hint = "        The Matrix            ";
	Data::GetInstance()->levels[9].hint = "           Inverse             ";
	Data::GetInstance()->levels[10].hint = "       In Soviet Russia:       ";

	//defining levels
	Data::GetInstance()->levels[1].gravity = 700.0f;
	Data::GetInstance()->levels[2].input = altInput;
	Data::GetInstance()->levels[7].render = TrippyRender;
	for (int i = 0; i < 5; i++)
	{
		Data::GetInstance()->teles[i] = true;
	}
	Data::GetInstance()->levels[3].input = teleport;
	Data::GetInstance()->levels[4].gravity = 700.0f;
	Data::GetInstance()->levels[4].input = altInput;
	Data::GetInstance()->levels[9].collision = collision;

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

	//Sounds 
	m_hBackgroundMusic = AudioManager::GetInstance()->LoadAudio("Assets/Audio/Game_Music.wav");
	m_hWin[0] = AudioManager::GetInstance()->LoadAudio("Assets/Audio/Win_1.wav");
	m_hWin[1] = AudioManager::GetInstance()->LoadAudio("Assets/Audio/Win_2.wav");

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
	if (AudioManager::GetInstance()->IsAudioPlaying(m_hBackgroundMusic))
	{
		AudioManager::GetInstance()->StopAudio(m_hBackgroundMusic);
	}
}

int GameState::Update(float dt)
{
	if (Data::GetInstance()->leveliter >= 11)
		return 3;
	if (!AudioManager::GetInstance()->IsAudioPlaying(m_hBackgroundMusic))
	{
		AudioManager::GetInstance()->PlayAudio(m_hBackgroundMusic,true);
	}

	if (Data::GetInstance()->leveliter == 8)
	{
		dt /= 2.0f;
	}

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
	key->Update(dt, Player::GetInstance());
	
		m_pLevel->Update(dt);

		// Check collisions
		CheckObstacleCollisions();

		// Player world collision
		m_pLevel->GetTiles()->CheckCollision(Player::GetInstance());

		if (m_fFadeTimer <= 0.0f)
		{
			Player::GetInstance()->Input(m_pLevel->GetTiles());
		}

		if (Player::GetInstance()->GetDead())
		{
			ResetLevel();
		}

		// End of loop
		if (m_fQuoteTimer > 0.0f)
		{
			m_fQuoteTimer -= dt;
		}
	}
	UpdateFade(dt);
	return playing;
}

void GameState::NextLevel()
{
	Data::GetInstance()->leveliter++;
	if (Data::GetInstance()->leveliter == 6)
	{
		Player::GetInstance()->SetInception(true);
	}
	else
	{
		Player::GetInstance()->SetInception(false);
	}
	m_fQuoteTimer = 2.5f;
	ResetLevel();
	if (Data::GetInstance()->leveliter >= 11)
	{
		//time to end the game and go to credits
		playing = 3;
	}
}

void GameState::Render()
{
	Data * data = Data::GetInstance();

	if (data->levels[data->leveliter].render)
	{
		data->levels[data->leveliter].render(this);
		return;
	}

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
	if (data->leveliter != 5)
	{
		m_pLevel->Render();
	}

	if (m_fQuoteTimer > 0.0f && m_fQuoteTimer <= 2.0f)
	{
		std::ostringstream info;
		info << Data::GetInstance()->levels[Data::GetInstance()->leveliter].hint;
		float scale = (2.0f - m_fQuoteTimer) + 1.0f;
		SGD::Color quoteColor = { (unsigned char)((m_fQuoteTimer / 2.0f) * 255), 0, 0, 0 };
		if (Data::GetInstance()->leveliter == 5)
		{
			quoteColor.red = quoteColor.green = quoteColor.blue = 255;
		}
		font->Draw(info.str().c_str(), { 400.0f - (2.0f - m_fQuoteTimer) * 100.0f, 350.0f }, scale, quoteColor);
	}
	#pragma region Pause Menu

	if (paused == true && m_fFade <= 0.0f)
	{
		font->Draw("Paused", { 672 - font->Center("Paused"), 100 }, 1, { 0, 0, 0 });
		font->Draw("~~~~~~", { 672 - font->Center("~~~~~~"), 120 }, 1, { 0, 0, 0 });

		if (cursor == 0)
			font->Draw("Resume", { 672 - font->Center("Resume"), 300 }, 1, { 255, 0, 0 }); // Resume selected
		else					    
			font->Draw("Resume", { 672 - font->Center("Resume"), 300 }, 1, { 0, 0, 0 }); // Resume unselected

		if (cursor == 1)
			font->Draw("Exit", { 672 - font->Center("Exit"), 350 }, 1, { 255, 0, 0 }); // Exit selected
		else
			font->Draw("Exit", { 672 - font->Center("Exit"), 350 }, 1, { 0, 0, 0 }); // Exit unselected 
	}
	
#pragma endregion

	if (m_fFade > 0.0f)
	{
		SGD::Color color = { (unsigned char)((m_fFade / 255.0f) * 255), 0, 0, 0 };
		SGD::Rectangle rect = { 0.0f, 0.0f, 1344.0f, 768.0f };
		graphics->DrawRectangle(rect, color, { 0, 0, 0 }, 0);
	}

}

void GameState::AltRender()
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
	m_pLevel->AltRender();

	if (m_fQuoteTimer > 0.0f && m_fQuoteTimer <= 2.0f)
	{
		std::ostringstream info;
		info << Data::GetInstance()->levels[Data::GetInstance()->leveliter].hint;
		float scale = (2.0f - m_fQuoteTimer) + 1.0f;
		SGD::Color quoteColor = { (unsigned char)((m_fQuoteTimer / 2.0f) * 255), 0, 0, 0 };
		font->Draw(info.str().c_str(), { 400.0f - (2.0f - m_fQuoteTimer) * 100.0f, 350.0f }, scale, quoteColor);
	}
#pragma region Pause Menu

	if (paused == true && m_fFade <= 0.0f)
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

	if (m_fFade > 0.0f)
	{
		SGD::Color color = { (unsigned char)((m_fFade / 255.0f) * 255), 0, 0, 0 };
		SGD::Rectangle rect = { 0.0f, 0.0f, 1344.0f, 768.0f };
		graphics->DrawRectangle(rect, color, { 0, 0, 0 }, 0);
	}

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
	Player::GetInstance()->SetVelocity({ 0.0f, 0.0f });
	Player::GetInstance()->SetPositive(false);
	key->SetPosition(key->GetStartPos()); 
	m_fFadeTimer = 1.0f;
	for (int i = 0; i < 5; i++)
	{
		Data::GetInstance()->teles[i] = true;
	}
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
	key->SetPosition({ 1184, 512 });
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

void GameState::UpdateFade(float _dt)
{
	if (m_fFadeTimer > 0.5f)
	{
		m_fFade += ((1.0f / 0.5f) * 255.0f) * _dt;
	}
	else if (m_fFadeTimer > 0.0f)
	{
		m_fFade -= ((1.0f / 0.5f) * 255.0f) * _dt;
	}

	if (m_fFade > 255.0f)
	{
		m_fFade = 255.0f;
	}
	else if (m_fFade < 0.0f)
	{
		m_fFade = 0.0f;
	}

	if (m_fFadeTimer > 0.0f)
	{
		m_fFadeTimer -= _dt;
	}
	else
	{
		m_fFade = 0.0f;
	}
}