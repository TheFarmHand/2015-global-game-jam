#pragma once
#include "BaseState.h"
#include "BitmapFont.h"
#include "../game_jam/WRAPPERS/SGD_Declarations.h"
#include "../game_jam/WRAPPERS/SGD_Handle.h"
#include "../game_jam/WRAPPERS/SGD_AudioManager.h"


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
	SGD::HAudio m_hBackgroundMusic;
	SGD::HAudio m_hWin[2];
	int playing = 0;
	Level *  m_pLevel;
	bool paused = false;
	ObjectManager * m_pObjManager;
	bool options = false;
	BitmapFont *font = nullptr;
	int cursor = 0;
	int optionsCursor = 0;
	SGD::HTexture	m_tBackgrounds[11];
	float m_fFade;
	float m_fFadeTimer;
	float m_fQuoteTimer = 0.0f;

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
	void AltRender();
	virtual void Input() override;

	void ResetLevel();
	void NextLevel();
	void CreateObstacles();
	void CheckObstacleCollisions();
	void UpdateFade(float _dt);
};

