#pragma once
#include "BaseState.h"
class MenuState :
	public BaseState
{
private:
	bool running = true;
public:
	MenuState();
	~MenuState();

	virtual bool Update(float dt);
	virtual void Render();
	virtual void Input();
};

