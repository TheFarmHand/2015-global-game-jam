#pragma once
#include "BaseState.h"
#include "Level.h"
class Tiles;
class GameState :
	public BaseState
{
private:
	int playing = 0;
	Level level;
	//Tiles * m_tTiles;
public:
	GameState();
	virtual ~GameState();

	virtual int Update(float dt) override;
	virtual void Render() override;
	virtual void Input() override;
};

