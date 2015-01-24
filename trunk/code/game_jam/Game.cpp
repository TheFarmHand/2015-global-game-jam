#include "Game.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_AudioManager.h"
#include "MenuState.h"
#include "GameState.h"
#include <time.h>
#include <Windows.h>
Game::Game()
{
}


Game::~Game()
{
}


void Game::Initialialize()
{
	//create stuff
	SGD::InputManager * input = SGD::InputManager::GetInstance();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * audio = SGD::AudioManager::GetInstance();

	input->Initialize();
	graphics->Initialize();
	audio->Initialize();

	MenuState *menu = new MenuState();
	GameState *play = new GameState();
	NewState(menu);

	//set up deltatime
	lasttime = GetTickCount();
}
void Game::Terminate()
{
	delete currstate;

	//destroy stuff
	SGD::InputManager * input = SGD::InputManager::GetInstance();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * audio = SGD::AudioManager::GetInstance();

	input->Terminate();
	input->DeleteInstance();
	graphics->Terminate();
	graphics->DeleteInstance();
	audio->Terminate();
	audio->DeleteInstance();

}
bool Game::Update()
{
	
	SGD::InputManager * input = SGD::InputManager::GetInstance();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * audio = SGD::AudioManager::GetInstance();


	//update the wrappers
	input->Update();
	graphics->Update();
	audio->Update();
	//return false in order to end game
	if (input->IsKeyDown(SGD::Key::A) && input->IsKeyDown(SGD::Key::Backspace))
		return false;

	//calculate deltatime
	unsigned int nowtime = GetTickCount();
	float deltatime = (nowtime - lasttime) / 1000.0f;
	if (deltatime < 0.0125f)
	{
		deltatime = 0.0125f;
	}
	lasttime = nowtime;
	//update the current state
	currstate->Input();

	int returnVal;
	returnVal = currstate->Update(deltatime);

	if (returnVal == 1)
		NewState(new MenuState);
	else if (returnVal == 2)
		NewState(new GameState);
	else if (returnVal == 3)
		return false;

	return true;
}
void const Game::Render()
{
	//render stuff
	currstate->Render();
}

void Game::NewState(BaseState * _state)
{
	delete currstate;
	currstate = nullptr;
	currstate = _state;
}