#pragma once
#include "BaseState.h"

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
	ObjectManager * m_pObjManager;

public:
	GameState();
	virtual ~GameState();

	virtual int Update(float dt) override;
	virtual void Render() override;
	virtual void Input() override;
};

