#include "Level.h"

////////////////////
// Includes
#include "Tiles.h"


Level::Level()
{
	manageobj.ClearAndDeleteAll();
	m_tTiles = new Tiles();
	m_tTiles->LoadLevel("Assets/TestLevel.xml");
}


Level::~Level()
{
	manageobj.ClearAndDeleteAll();
	delete m_tTiles;
	m_tTiles = nullptr;
}

void Level::Update(float dt)
{
	
}
void Level::Render()
{
	// Draw the background first
	//m_tTiles->RenderImageLayer(true);

	// Anything between back and foreground
	m_tTiles->RenderCollision();

	// Draw foreground last
	//m_tTiles->RenderImageLayer(false);
}
void Level::Input()
{
	
}

void Level::Incrementlevel()
{
	//here we add 1 to the level
	//then we take the data from the array of leveldata and populate
	
}
