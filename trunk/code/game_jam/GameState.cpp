#include "GameState.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"

GameState::GameState()
{
}


GameState::~GameState()
{
}

bool GameState::Update(float dt)
{
	
	int x = 0;
	return playing;
}
void GameState::Render()
{
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	graphics->DrawString("This is the Game State", { 50.0f, 50.0f }, { 255, 255, 255 });
}
void GameState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyDown(SGD::Key::Escape))
		playing = false;
}
