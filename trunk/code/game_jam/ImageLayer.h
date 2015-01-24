//***********************************************************************
//	File:		ImageLayer.h
//	Author:		Michael Sciortino
//	Course:		GameJam 2015
//	Purpose:	The ImageLayer class will hold all necessary information for a
//				single image layer and handle drawing
//***********************************************************************

#pragma once

/////////////////////////
// Includes
#include "../game_jam/WRAPPERS/SGD_Declarations.h"
#include "../game_jam/WRAPPERS/SGD_Handle.h"
class ImageLayer
{
public:
	//////////////////////////////
	// Ctor/Dtor
	ImageLayer();
	~ImageLayer();

	//////////////////////////////
	// Accessors
	int				GetWidth()			const		{ return m_nWidth; }
	int				GetHeight()			const		{ return m_nHeight; }
	int				GetDepth()			const		{ return m_nDepth; }
	int				GetTileSetWidth()	const		{ return m_nTileSetWidth; }
	int				GetTileSetHeight()	const		{ return m_nTileSetHeight; }
	int				GetTileSetSize()	const		{ return m_nTileSetSize; }
	int**			GetImageLayer()		const		{ return m_nnImageLayer; }
	SGD::HTexture	GetTexture()		const		{ return m_tTileSet; }

	//////////////////////////////
	// Mutators
	void		SetWidth(int _width)					{ m_nWidth = _width; }
	void		SetHeight(int _height)					{ m_nHeight = _height; }
	void		SetDepth(int _depth)					{ m_nDepth = _depth; }
	void		SetTileSetWidth(int _width)				{ m_nTileSetWidth = _width; }
	void		SetTileSetHeight(int _height)			{ m_nTileSetHeight = _height; }
	void		SetTileSetSize(int _size)				{ m_nTileSetSize = _size; }
	void		SetImageLayer(int** _imageLayer)		{ m_nnImageLayer = _imageLayer; }
	void		SetTexture(SGD::HTexture _tex)			{ m_tTileSet = _tex; }

private:
	//////////////////////////////
	// Member fields
	int				m_nWidth;
	int				m_nHeight;
	int				m_nDepth;
	int				m_nTileSetWidth;
	int				m_nTileSetHeight;
	int				m_nTileSetSize;
	int**			m_nnImageLayer;
	SGD::HTexture	m_tTileSet;

};