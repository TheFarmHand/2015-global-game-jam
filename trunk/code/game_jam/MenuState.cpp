#include "MenuState.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"

MenuState::MenuState()
{
	font = new BitmapFont;
	font->Initialize("Assets/Font.fnt");
}

MenuState::~MenuState()
{
	font->Terminate();
	delete font;

}

int MenuState::Update(float dt)
{
	

	return running;
}

void MenuState::Render()
{
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();

	font->Draw("Main Menu", { 400, 50 } , 1, { 255, 255, 255 });

	if (cursor == 0)
		font->Draw("Play", { 425, 250 }, 1, { 0, 255, 255 }); // Play selected
	else
		font->Draw("Play", { 425, 250 }, 1, { 255, 255, 255 }); // Play unselected

	if (cursor == 1)
		font->Draw("Options", { 405, 300 }, 1, { 0, 255, 255 }); // Options selected
	else
		font->Draw("Options", { 405, 300 }, 1, { 255, 255, 255 }); // Options unselected

	if (cursor == 2)
		font->Draw("Exit", { 425, 350 }, 1, { 0, 255, 255 }); // Exit selected
	else
		font->Draw("Exit", { 425, 350 }, 1, { 255, 255, 255 }); // Exit unselected


}

void MenuState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyPressed(SGD::Key::W) || input->IsKeyPressed(SGD::Key::UpArrow)) // Menu up
		cursor -= 1;
	else if (input->IsKeyPressed(SGD::Key::S) || input->IsKeyPressed(SGD::Key::DownArrow)) // Menu down
		cursor += 1;

	if (input->IsKeyPressed(SGD::Key::Escape))
		cursor = 2;

	if (input->IsKeyPressed(SGD::Key::Enter)) // Select
	{
		if (cursor == 0)
			running = 2;
		else if (cursor == 2)
			running = 3;

	}

	if (cursor < 0)
		cursor = 2;
	else if (cursor > 2)
		cursor = 0;
}
