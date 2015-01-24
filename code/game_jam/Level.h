#pragma once
#include "ObjectManager.h"
#
class Level
{
private:
	ObjectManager manageobj;//this will hold the objects in the level

public:
	Level();
	~Level();

	void Update(float dt);
	void Render();
	void Input();
};

