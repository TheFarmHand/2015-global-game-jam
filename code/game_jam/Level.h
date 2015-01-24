#pragma once
#include "ObjectManager.h"

/////////////////////////
// Forward declarations
class Tiles;

class Level
{
private:
	ObjectManager manageobj;//this will hold the objects in the level
	Tiles * m_tTiles;
	float gravity = -9.81f;
	
	

public:
	Level();
	~Level();

	void Update(float dt);
	void Render();
	void Input();


	//////////////////////////
	// Accessors
	Tiles *		GetTiles() const		{ return m_tTiles; }
};

