#pragma once
#include "BaseState.h"
class GameState :
	public BaseState
{
private:
	bool playing = true;
public:
	GameState();
	virtual ~GameState();

	virtual bool Update(float dt);
	virtual void Render();
	virtual void Input();
};

