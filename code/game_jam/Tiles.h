//***********************************************************************
//	File:		Tiles.h
//	Author:		Michael Sciortino
//	Course:		GameJam 2015
//	Purpose:	The tiles class will hold information for the colision layer and
//				any image layers
//***********************************************************************

#pragma once

/////////////////////////
// Forward declarations
class ImageLayer;

/////////////////////////
// Definitions
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

/////////////////////////
// Includes
#include "../game_jam/WRAPPERS/SGD_GraphicsManager.h"
#include <vector>

class Tiles
{
public:
	//////////////////////////////
	// Ctor/Dtor
	Tiles();
	~Tiles();

	//////////////////////////////
	// Main methods
	bool		LoadLevel(const char * _path);
	void		RenderCollision();
	void		RenderImageLayer(bool _background);
	
	//////////////////////////////
	// Accessors
	int			GetWidth() const			{ return m_nWidth; }
	int			GetHeight() const			{ return m_nHeight; }
	int**		GetCollisionLayer() const	{ return m_nnCollisionLayer; }

	//////////////////////////////
	// Mutators
	void		SetWidth(int _width)				{ m_nWidth = _width; }
	void		SetHeight(int _height)				{ m_nHeight = _height; }
	void		SetCollisionLayer(int** _layer)		{ m_nnCollisionLayer = _layer; }

private:
	//////////////////////////////
	// Member fields
	int						m_nWidth;
	int						m_nHeight;
	int**					m_nnCollisionLayer;
	std::vector<ImageLayer*>		m_vlLayers;

};