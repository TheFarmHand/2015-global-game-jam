#include "GameState.h"
#include "Tiles.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
#include "Player.h"
#include "FallingPlatform.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//For Testing
static FallingPlatform TheSpring;

GameState::GameState()
{
	
	
}


GameState::~GameState()
{
	
}

int GameState::Update(float dt)
{
	TheSpring.Update(dt);
	Player::GetInstance()->Update(dt);
	level.Update(dt);
	//Player::GetInstance()->ApplyGravity();	
	int x = 0;
	return playing;
}
void GameState::Render()
{
	TheSpring.Render();
	Player::GetInstance()->Render();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	level.Render();
	// Draw anything that needs to always be seen here
}
void GameState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyDown(SGD::Key::Escape))
		playing = false;
}
