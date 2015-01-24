#pragma once
#include "ObjectManager.h"
#include "Tiles.h"


class Level
{
private:
	ObjectManager manageobj;//this will hold the objects in the level
	Tiles * tiles;
	float gravity = -9.81f;
	
	

public:
	Level();
	~Level();

	void Update(float dt);
	void Render();
	void Input();

	void Incrementlevel();
};

