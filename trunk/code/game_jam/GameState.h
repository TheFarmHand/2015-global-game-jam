#pragma once
#include "BaseState.h"
#include "BitmapFont.h"
#include "../game_jam/WRAPPERS/SGD_Declarations.h"
#include "../game_jam/WRAPPERS/SGD_Handle.h"


/////////////////////////
// Forward declarations
class Tiles;
class Level;
class ObjectManager;
class Spring;
class FallingPlatform;
class WalkThrough;
class LKey;

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
	SGD::HTexture	m_tBackgrounds[11];


	Spring * spring1;
	Spring * spring2;
	Spring * spring3;
	FallingPlatform * platform;
	LKey * key;


public:
	GameState();
	virtual ~GameState();

	virtual int Update(float dt) override;
	virtual void Render() override;
	virtual void Input() override;

	void ResetLevel();
	void NextLevel();
	void CreateObstacles();
	void CheckObstacleCollisions();
};

