#pragma once
#include "BaseState.h"
#include "BitmapFont.h"


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

	Spring * spring1;
	Spring * spring2;
	Spring * spring3;
	FallingPlatform * platform;
	WalkThrough * walkThrough1;
	WalkThrough * walkThrough2;
	LKey * key;

public:
	GameState();
	virtual ~GameState();

	virtual int Update(float dt) override;
	virtual void Render() override;
	virtual void Input() override;

	void ResetLevel();
	void CreateObstacles();
	void CheckObstacleCollisions();
};

