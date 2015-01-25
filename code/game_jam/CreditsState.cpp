#include "CreditsState.h"

#include "WRAPPERS\SGD_GraphicsManager.h"
#include "WRAPPERS\SGD_InputManager.h"


CreditsState::CreditsState()
{
	font = new BitmapFont;
	font->Initialize("Assets/Font.fnt");
	creditsBackground = SGD::GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/TitleScreen.png");
}


CreditsState::~CreditsState()
{
	font->Terminate();
	delete font;
}

int CreditsState::Update(float _dt)
{
	position -= 80 * _dt;

	if (position < -1600)
		running = 1;

	return running;
}

void CreditsState::Render()
{
	SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();

	graphics->DrawTexture(creditsBackground, { 0, 0 }, 0, { 0, 0 }, { 255, 255, 255 }, { 1, 1 });

	font->Draw("Programmers:", { 680 - font->Center("Programmers:"), 800 + position }, 1, { 0, 100, 100 });
	font->Draw("~~~~~~~~~~~", { 680 - font->Center("~~~~~~~~~~~"), 820 + position }, 1, { 0, 100, 100 });

	font->Draw("Nick Dalton", { 680 - font->Center("Nick Dalton"), 900 + position }, 1, { 0, 100, 100 });
	font->Draw("Luis Garcia", { 680 - font->Center("Luis Garcia"), 1000 + position }, 1, { 0, 100, 100 });
	font->Draw("Mike Sciortino", { 680 - font->Center("Mike Sciortino"), 1100 + position }, 1, { 0, 100, 100 });
	font->Draw("Riley Wood", { 680 - font->Center("Riley Wood"), 1200 + position }, 1, { 0, 100, 100 });

	font->Draw("Artist:", { 680 - font->Center("Artist:"), 1400 + position }, 1, { 0, 100, 100 });
	font->Draw("~~~~~", { 680 - font->Center("~~~~~"), 1420 + position }, 1, { 0, 100, 100 });

	font->Draw("Kelly McCarthy", { 680 - font->Center("Kelly McCarthy"), 1500 + position }, 1, { 0, 100, 100 });
}

void CreditsState::Input()
{
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape))
		running = 1;
}