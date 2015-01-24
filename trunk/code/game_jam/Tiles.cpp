//***********************************************************************
//	File:		Tiles.cpp
//	Author:		Michael Sciortino
//	Course:		GameJam 2015
//	Purpose:	The tiles class will hold information for the colision layer and
//				any image layers
//***********************************************************************

//////////////////////////////
// Includes
#include "Tiles.h"
#include "ImageLayer.h"
#include "Object.h"
#include "TinyXML\tinyxml.h"

//////////////////////////////
// Constructor
Tiles::Tiles()
{

}

//////////////////////////////
// Destructor
Tiles::~Tiles()
{
	// Loop through and free each image layer
	for (unsigned int i = 0; i < m_vlLayers.size(); ++i)
	{
		delete m_vlLayers[i];
	}

	// Loop through and free the collision layer
	for (int i = 0; i < m_nWidth; ++i)
	{
		delete[] m_nnCollisionLayer[i];
	}
	delete m_nnCollisionLayer;
}

//////////////////////////////
// LoadLevel
// -Loads information into the level from the given path
bool Tiles::LoadLevel(const char * _path)
{
	//Create the tinyxml document 
	TiXmlDocument doc;

	// Load the file
	if (doc.LoadFile(_path) == false)
	{
		return false;
	}

	// Grab reference to the root
	TiXmlElement* pRoot = doc.RootElement();
	if (pRoot == nullptr)
	{
		return false;
	}

	// Read in width and height of the map
	pRoot->Attribute("width", &m_nWidth);
	pRoot->Attribute("height", &m_nHeight);

	// Load in the image layers by finding out how many there are
	TiXmlElement* pImageLayers = pRoot->FirstChildElement();
	int numLayers = 0;
	pImageLayers->Attribute("numLayers", &numLayers);

	// Read in each image layer
	TiXmlElement * pImageLayer = pImageLayers->FirstChildElement();
	for (int i = 0; i < numLayers; ++i)
	{
		// Create an empty layer
		ImageLayer * imageLayer = new ImageLayer;

		// Set individual values

		// depth
		int depth;
		pImageLayer->Attribute("depth", &depth);
		imageLayer->SetDepth(depth);

		// tileset dimensions
		int tileSetWidth;
		pImageLayer->Attribute("tileSetWidth", &tileSetWidth);
		imageLayer->SetTileSetWidth(tileSetWidth);
		int tileSetHeight;
		pImageLayer->Attribute("tileSetHeight", &tileSetHeight);
		imageLayer->SetTileSetHeight(tileSetHeight);
		int tileSetSize;
		pImageLayer->Attribute("tileSetSize", &tileSetSize);
		imageLayer->SetTileSetSize(tileSetSize);

		// tileset texture
		std::string path = "";
		path += pImageLayer->Attribute("image");
		path = path.erase(0, 1);
		SGD::HTexture texture = SGD::GraphicsManager::GetInstance()->LoadTexture(path.c_str());
		imageLayer->SetTexture(texture);

		// Read in tiles
		int ** info = new int*[m_nWidth];
		TiXmlElement* pTile = pImageLayer->FirstChildElement();
		for (int xx = 0; xx < m_nWidth; ++xx)
		{
			info[xx] = new int[m_nHeight];
			for (int yy = 0; yy < m_nHeight; ++yy)
			{
				int value = 0;
				pTile->Attribute("type", &value);
				info[xx][yy] = value;
				pTile = pTile->NextSiblingElement();
			}
		}

		// Assign the tile info and push the layer into the vector
		imageLayer->SetImageLayer(info);
		imageLayer->SetWidth(m_nWidth);
		imageLayer->SetHeight(m_nWidth);
		m_vlLayers.push_back(imageLayer);

		// Read in the next layer
		pImageLayer = pImageLayer->NextSiblingElement();
	}

	// Read in the collision layer
	TiXmlElement * pCollisionLayer = pImageLayers->NextSiblingElement();

	// Read in tiles
	m_nnCollisionLayer = new int*[m_nWidth];
	TiXmlElement* pTile = pCollisionLayer->FirstChildElement();
	for (int xx = 0; xx < m_nWidth; ++xx)
	{
		m_nnCollisionLayer[xx] = new int[m_nHeight];
		for (int yy = 0; yy < m_nHeight; ++yy)
		{
			int value = 0;
			pTile->Attribute("type", &value);
			m_nnCollisionLayer[xx][yy] = value;
			pTile = pTile->NextSiblingElement();
		}
	}

	// Load in worked!
	return true;
}

//////////////////////////////
// RenderLevel
// -Draws all image layers to the screen
// -If _collision then render the collision layer as well
void Tiles::RenderCollision()
{
	// Handle to graphics manager
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	// Loop through the map
	for (int xx = 0; xx < m_nWidth; ++xx)
	{
		for (int yy = 0; yy < m_nHeight; ++yy)
		{
			// Determine color based on tile type
			int value = m_nnCollisionLayer[xx][yy];
			SGD::Color color = { 0, 0, 0 };

			switch (value)
			{
				// Walls
				case 0:
					color = { 150, 150, 150 }; // gray
					break;
					// Death
				case 1:
					color = { 255, 150, 150 }; // red
					break;
					// Left ramp
				case 2:
					color = { 160, 80, 250 }; // purple
					break;
					// Right ramp
				case 3:
					color = { 250, 70, 210 }; // pink
					break;
					// Ice
				case 4:
					color = { 0, 220, 220 }; // Cyan
					break;
					// Ice left ramp
				case 5:
					color = { 50, 110, 0 }; // dark green
					break;
					// Ice right ramp
				case 6:
					color = { 30, 220, 0 }; // light green
					break;

			}

			// Don't draw empty tiles
			if (value != -1)
			{
				// Rectangle for drawing
				SGD::Rectangle rect = { xx * 32.0f, yy * 32.0f, xx * 32.0f + 32, yy * 32.0f + 32 };
				pGraphics->DrawRectangle(rect, color, { 0, 0, 0 }, 2);
			}
		}
	}
}

//////////////////////////////
// RenderBackground
// - Render all image layers with a depth lower than 0
void Tiles::RenderImageLayer(bool _background)
{
	// Handle to graphics manager
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	// Loop through each layer
	for (unsigned int i = 0; i < m_vlLayers.size(); ++i)
	{
		// Reference to the alyer
		ImageLayer * layer = m_vlLayers[i];

		// Only render layers that have a depth lower than 0 if background
		// greater than or equal to 0 if not
		if ((_background && layer->GetDepth() < 0) ||
			(!_background && layer->GetDepth() >= 0))
		{
			// Loop through the map
			for (int xx = 0; xx < m_nWidth; ++xx)
			{
				for (int yy = 0; yy < m_nHeight; ++yy)
				{
					// Type of tile
					int type = layer->GetImageLayer()[xx][yy];

					// Only render tiles that have a value
					if (type != -1)
					{
						// Section on the tileset
						int width = layer->GetTileSetWidth();
						int height = layer->GetTileSetHeight();
						int size = layer->GetTileSetSize();
						SGD::Rectangle section = SGD::Rectangle(
							type % width * size * 1.0f,
							type / width * size * 1.0f,
							type % width * size + 32.0f,
							type / width * size + 32.0f
							);

						// Draw the tile
						pGraphics->DrawTextureSection(
							layer->GetTexture(),
							{ xx * 32.0f, yy * 32.0f },
							section,
							0.0f,
							{ 0.0f, 0.0f },
							{ 255, 255, 255 },
							{ 1.0f, 1.0f });

						//	Camera::GetInstance()->DrawTexture({ xx * 32.0f - Camera::GetInstance()->GetCameraPos().x * layer->GetScrollSpeed(),
						//		yy * 32.0f - Camera::GetInstance()->GetCameraPos().y * layer->GetScrollSpeed() }, 0.0f, layer->GetTileSet(), false);
					}

				}
			}
		}
	}
}

//////////////////////////////
// CheckCollision
// - Handles collision with the passed in entity and collision layer
void Tiles::CheckCollision(Object * _obj)
{
	//SGD::Rectangle rect = _obj->GetRect();
	//// Determine the position of the enity in the array
	//int x = (int)(rect.left / 32);
	//int y = (int)(rect.top / 32);

	//// Determine how far to check
	//int width = (int)((rect.right - 1 - rect.left) / 32);
	//int height = (int)((rect.bottom - 1 - rect.top) / 32);

	////int x2 = (int)((rect.right - 1) / 32);
	////int y2 = (int)((rect.bottom - 1) / 32);

	//// loop through all adjacent collision pieces
	//for (int xx = x; xx <= x + width + 1; ++xx)
	//{
	//	for (int yy = y; yy <= y + height + 1; ++yy)
	//	{
	//		// Check if the current piece is in the bounds of the array
	//		if (xx >= 0 && xx < m_nWidth && yy >= 0 && yy < m_nHeight)
	//		{
	//			// Figure out what is at this position
	//			int id = m_nnCollisionLayer[xx][yy];

	//			if (id != -1) // only check non empty tiles
	//			{
	//				// Use ID to determine which object to create and pass it in
	//				LevelCollider * collider = new LevelCollider();
	//				collider->SetPosition({ xx * 32.0f, yy * 32.0f });
	//				collider->SetSize({ 32, 32 });
	//				if (collider->GetRect().IsIntersecting(_entity->GetRect()))
	//				{
	//					collider->SetCollide(id);
	//					_entity->HandleCollision(collider);
	//				}
	//				delete collider;
	//			}
	//		}
	//	}
	//}
}