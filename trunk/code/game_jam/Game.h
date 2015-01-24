#pragma once
#include "BaseState.h"
class Game
{
private:
	BaseState * currstate = nullptr;

	unsigned int lasttime = 0;
public:
	void Initialialize();
	void Terminate();
	bool Update();
	void const Render();

	void NewState(BaseState * _state);//deletes current states memory, sets current state to pointer sent in



	Game();
	~Game();
};

