#pragma once
#include "BaseState.h"
class Tiles;
class GameState :
	public BaseState
{
private:
	bool playing = true;
	Tiles * m_tTiles;
public:
	GameState();
	virtual ~GameState();

	virtual bool Update(float dt);
	virtual void Render();
	virtual void Input();
};

