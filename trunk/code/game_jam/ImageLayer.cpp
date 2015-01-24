//***********************************************************************
//	File:		ImageLayer.cpp
//	Author:		Michael Sciortino
//	Course:		GameJam 2015
//	Purpose:	The ImageLayer class will hold all necessary information for a
//				single image layer and handle drawing
//***********************************************************************

#include "ImageLayer.h"
#include "../game_jam/WRAPPERS/SGD_GraphicsManager.h"

//////////////////////////////
// Constructor
ImageLayer::ImageLayer()
{
}

//////////////////////////////
// Destructor
ImageLayer::~ImageLayer()
{
	// Loop through and free the array
	for (int i = 0; i < m_nWidth; ++i)
	{
		delete[] m_nnImageLayer[i];
	}
	delete[] m_nnImageLayer;

	// release the texture
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_tTileSet);

}