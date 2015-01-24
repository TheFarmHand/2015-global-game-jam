#pragma once
#include "BaseState.h"
#include "BitmapFont.h"

class Tiles;

/////////////////////////
// Forward declarations
class Level;
class ObjectManager;

class GameState :
	public BaseState
{
private:
	int playing = 0;
	Level *  m_pLevel;
	bool paused = false;
	ObjectManager * m_pObjManager;
	bool options = false;


	BitmapFont *font = nullptr;
	int cursor = 0;
	int optionsCursor = 0;
public:
	GameState();
	virtual ~GameState();

	virtual int Update(float dt) override;
	virtual void Render() override;
	virtual void Input() override;
};

