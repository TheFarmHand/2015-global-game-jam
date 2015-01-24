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
	
	font = new BitmapFont;
	font->Initialize("Assets/Font.fnt");
}


GameState::~GameState()
{
	delete m_pLevel;
	m_pObjManager->ClearAndDeleteAll();
	delete m_pObjManager;

	font->Terminate();
	delete font;
}

int GameState::Update(float dt)
{
	if (!paused) // Make sure all gameplay code is inside here, otherwise pause won't work
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
	}
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
		Player::GetInstance()->SetPosition(Player::GetInstance()->GetStartPos());

	}
}


//BLASHDLASJHFlkj