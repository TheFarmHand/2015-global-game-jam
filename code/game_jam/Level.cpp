#include "Level.h"

////////////////////
// Includes
#include "Tiles.h"
#include "Data.h"

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
	manageobj.UpdateAll(dt);
}
void Level::Render()
{
	// Draw the background first
	m_tTiles->RenderImageLayer(true);
	// Anything between back and foreground
	//m_tTiles->RenderCollision();
	// Draw foreground last
	m_tTiles->RenderImageLayer(false);
}
void Level::Input()
{
	
}

void Level::AltRender()
{
	// Draw the background first
	m_tTiles->AltRenderImageLayer(true);
	// Anything between back and foreground
	//m_tTiles->RenderCollision();
	// Draw foreground last
	m_tTiles->AltRenderImageLayer(false);
}


