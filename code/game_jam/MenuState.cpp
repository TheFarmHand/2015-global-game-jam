#include "MenuState.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
#include "WRAPPERS\SGD_AudioManager.h"

MenuState::MenuState()
{
	font = new BitmapFont;
	font->Initialize("Assets/Font.fnt");
	menuBackground = SGD::GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/TitleScreen.png");
	menuMusic = SGD::AudioManager::GetInstance()->LoadAudio("Assets/Audio/Main_Menu.wav");
}

MenuState::~MenuState()
{
	font->Terminate();
	if (SGD::AudioManager::GetInstance()->IsAudioPlaying(menuMusic))
	{
		SGD::AudioManager::GetInstance()->StopAudio(menuMusic);
	}
	delete font;

}

int MenuState::Update(float dt)
{
	if (!SGD::AudioManager::GetInstance()->IsAudioPlaying(menuMusic))
	{
		SGD::AudioManager::GetInstance()->PlayAudio(menuMusic,true);
	}

	return running;
}

void MenuState::Render()
{
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();

	graphics->DrawTexture(menuBackground, { 0.0f, 0.0f }, 0.0f, { 0.0f, 0.0f }, { 255, 255, 255 }, { 1.0f, 1.0f });
	//font->Draw("Main Menu", { 512 - font->Center("Main Menu"), 50 }, 1, { 255, 255, 255 });
	//font->Draw("~~~~~~~~~", { 512 - font->Center("~~~~~~~~~"), 70 }, 1, { 255, 255, 255 });

	if (cursor == 0)
		font->Draw("Play", { 650 - font->Center("Play"), 700 }, 1, { 0, 100, 100 }); // Play selected
	else
		font->Draw("Play", { 650 - font->Center("Play"), 700 }, 1, { 0, 0, 0 }); // Play unselected

	if (cursor == 1)
		font->Draw("Exit", { 750 - font->Center("Exit"), 700 }, 1, { 0, 100, 100 }); // Exit selected
	else
		font->Draw("Exit", { 750 - font->Center("Exit"), 700 }, 1, { 0, 0, 0 }); // Exit unselected


}

void MenuState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::W) || input->IsKeyPressed(SGD::Key::LeftArrow) || input->GetLeftJoystick(0).y == 1) // Menu up
		cursor -= 1;
	else if (input->IsKeyPressed(SGD::Key::S) || input->IsKeyPressed(SGD::Key::RightArrow) || input->GetLeftJoystick(0).y == -1) // Menu down
		cursor += 1;

	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0,1))
		cursor = 2;

	if (input->IsKeyPressed(SGD::Key::Enter) || input->IsButtonPressed(0,0)) // Select
	{
		if (cursor == 0)
			running = 2;
		else if (cursor == 1)
			running = 3;

	}

	if (cursor < 0)
		cursor = 1;
	else if (cursor > 1)
		cursor = 0;
}
