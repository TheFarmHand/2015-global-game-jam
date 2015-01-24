#include "GameState.h"
#include "Tiles.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
#include "Player.h"
#include "DeathTouch.h"
#include "SolidWall.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//For Testing
static SolidWall TheSolidWall;

GameState::GameState()
{
	m_tTiles = new Tiles();
	m_tTiles->LoadLevel("Assets/TestLevel.xml");
	
}


GameState::~GameState()
{
	delete m_tTiles;
}

int GameState::Update(float dt)
{
	TheSolidWall.Update(dt);
	Player::GetInstance()->Update(dt);
	//Player::GetInstance()->ApplyGravity();	
	int x = 0;
	return playing;
}
void GameState::Render()
{
	TheSolidWall.Render();
	Player::GetInstance()->Render();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	//graphics->DrawString("This is the Game State", { 50.0f, 50.0f }, { 255, 255, 255 });

	// Draw the background first
	//m_tTiles->RenderImageLayer(true);

	// Anything between back and foreground
	//m_tTiles->RenderCollision();

	// Draw foreground last
	//m_tTiles->RenderImageLayer(false);

	// Draw anything that needs to always be seen here
}
void GameState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyDown(SGD::Key::Escape))
		playing = false;
}
