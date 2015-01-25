#pragma once
#include "BaseState.h"
#include "BitmapFont.h"
#include "WRAPPERS\SGD_GraphicsManager.h"

class CreditsState : public BaseState
{
	// Data Members //
	int cursor = 0;
	int running = 0;
	float position = 0;

	// Assets //
	SGD::HTexture creditsBackground = SGD::INVALID_HANDLE;

	BitmapFont* font = nullptr;

public:
	CreditsState();
	~CreditsState();

	// State Functions //
	virtual int Update(float _dt) override;
	virtual void Render() override;
	virtual void Input() override;
};

