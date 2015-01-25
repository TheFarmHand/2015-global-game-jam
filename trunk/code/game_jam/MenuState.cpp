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

	if (cursor == 0)
		font->Draw("Play", { 530 - font->Center("Play"), 700 }, 1, { 0, 100, 100 }); // Play selected
	else
		font->Draw("Play", { 530 - font->Center("Play"), 700 }, 1, { 0, 0, 0 }); // Play unselected

	if (cursor == 1)
		font->Draw("Credits", { 680 - font->Center("Credits"), 700 }, 1, { 0, 100, 100 }); // Credits selected
	else
		font->Draw("Credits", { 680 - font->Center("Credits"), 700 }, 1, { 0, 0, 0 }); // Credits unselected


	if (cursor == 2)
		font->Draw("Exit", { 830 - font->Center("Exit"), 700 }, 1, { 0, 100, 100 }); // Exit selected
	else
		font->Draw("Exit", { 830 - font->Center("Exit"), 700 }, 1, { 0, 0, 0 }); // Exit unselected


}

void MenuState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::A) || input->IsKeyPressed(SGD::Key::LeftArrow) || input->GetLeftJoystick(0).y == 1) // Menu left
		cursor -= 1;
	else if (input->IsKeyPressed(SGD::Key::D) || input->IsKeyPressed(SGD::Key::RightArrow) || input->GetLeftJoystick(0).y == -1) // Menu right
		cursor += 1;

	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0,1))
		cursor = 2;

	if (input->IsKeyPressed(SGD::Key::Enter) || input->IsButtonPressed(0,0)) // Select
	{
		if (cursor == 0)
			running = 2;
		else if (cursor == 1)
			running = 3;
		else if (cursor == 2)
			running = 4;

	}

	if (cursor < 0)
		cursor = 2;
	else if (cursor > 2)
		cursor = 0;
}
