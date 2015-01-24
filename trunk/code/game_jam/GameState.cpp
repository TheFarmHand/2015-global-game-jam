#include "GameState.h"
#include "Tiles.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Level.h"
#include "FallingPlatform.h"
#include "WalkThrough.h"
#include "Key.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//For Testing
static WalkThrough TheSpring;
static FallingPlatform fp;
static LKey TheKey;

GameState::GameState()
{
	m_pLevel = new Level();
	m_pObjManager = new ObjectManager();
}


GameState::~GameState()
{
	delete m_pLevel;
	m_pObjManager->ClearAndDeleteAll();
	delete m_pObjManager;
}

int GameState::Update(float dt)
{
	TheSpring.Update(dt);
	fp.Update(dt);
	TheKey.Update(dt);

	Player::GetInstance()->Update(dt);
	m_pLevel->Update(dt);

	// Check collision
	if (Player::GetInstance()->GetRect().IsIntersecting(fp.GetRect()))
	{
		Player::GetInstance()->HandleCollision(&fp);
		fp.HandleCollision(Player::GetInstance());
	}
	m_pLevel->GetTiles()->CheckCollision(Player::GetInstance());

	// End of loop
	return playing;
}
void GameState::Render()
{
	TheSpring.Render();
	fp.Render();
	TheKey.Render();
	Player::GetInstance()->Render();
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	m_pLevel->Render();
	// Draw anything that needs to always be seen here
}
void GameState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyDown(SGD::Key::Escape))
		playing = false;
}
