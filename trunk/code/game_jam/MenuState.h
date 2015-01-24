#pragma once
#include "BaseState.h"
#include "BitmapFont.h"

class MenuState : public BaseState
{
	// Data Members //
	int cursor = 0;
	int running = 0;

	// Assets //
	SGD::HAudio menuMusic = SGD::INVALID_HANDLE;
	SGD::HAudio menuMove = SGD::INVALID_HANDLE;
	SGD::HAudio menuSelect = SGD::INVALID_HANDLE;

	SGD::HTexture menuBackground = SGD::INVALID_HANDLE;
	SGD::HTexture menuButton = SGD::INVALID_HANDLE;
	SGD::HTexture menuLogo = SGD::INVALID_HANDLE;

	BitmapFont *font = nullptr;

public:
	// Singleton //
	MenuState();
	~MenuState();

	// State Functions //
	virtual int Update(float dt) override;
	virtual void Render() override;
	virtual void Input() override;
};

