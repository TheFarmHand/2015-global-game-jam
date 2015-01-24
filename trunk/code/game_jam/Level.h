#pragma once
#include "ObjectManager.h"
#
class Level
{
private:
	ObjectManager manageobj;//this will hold the objects in the level
	float gravity = -9.81f;
	unsigned int leveliter = 0;

public:
	Level();
	~Level();

	void Update(float dt);
	void Render();
	void Input();
};

