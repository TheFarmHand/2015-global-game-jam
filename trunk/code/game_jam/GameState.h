#pragma once
#include "BaseState.h"
class Tiles;
class GameState :
	public BaseState
{
private:
	int playing = 0;

	Tiles * m_tTiles;
public:
	GameState();
	virtual ~GameState();

	virtual int Update(float dt) override;
	virtual void Render() override;
	virtual void Input() override;
};

