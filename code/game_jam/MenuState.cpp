#include "MenuState.h"
#include "WRAPPERS/SGD_InputManager.h"
#include "WRAPPERS/SGD_GraphicsManager.h"
MenuState::MenuState()
{

}


MenuState::~MenuState()
{

}

bool MenuState::Update(float dt)
{
	
	return running;
}
void MenuState::Render()
{
	SGD::GraphicsManager * graphics = SGD::GraphicsManager::GetInstance();
	graphics->DrawString("This is the Menu State", { 50.0f, 50.0f }, { 255, 255, 255 });
}
void MenuState::Input()
{
	SGD::InputManager * input = SGD::InputManager::GetInstance();

	if (input->IsKeyDown(SGD::Key::Escape))
		running = false;
}
