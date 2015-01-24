#include "Level.h"



Level::Level()
{
	manageobj.ClearAndDeleteAll();
	tiles = new Tiles();
	tiles->LoadLevel("Assets/TestLevel.xml");
}


Level::~Level()
{
	manageobj.ClearAndDeleteAll();
	delete tiles;
	tiles = nullptr;
}

void Level::Update(float dt)
{
	
}
void Level::Render()
{
	// Draw the background first
	tiles->RenderImageLayer(true);

	// Anything between back and foreground
	tiles->RenderCollision();

	// Draw foreground last
	tiles->RenderImageLayer(false);
}
void Level::Input()
{
	
}

void Level::Incrementlevel()
{
	//here we add 1 to the level
	//then we take the data from the array of leveldata and populate
	
}
