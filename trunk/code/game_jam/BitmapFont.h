/***************************************************************
|	File:		BitmapFont.h
|	Author:		Nick Dalton
|	Course:		SGD 1407
|	Purpose:	BitmapFont class draws text using an image
|				of fixed-size character glyphs
***************************************************************/

#ifndef BITMAPFONT_H
#define BITMAPFONT_H


#include "WRAPPERS/SGD_Handle.h"
#include "WRAPPERS/SGD_Color.h"
#include "WRAPPERS/SGD_Geometry.h"

#include <vector>


/**************************************************************/
// BitmapFont class
//	- displays text using an image of fixed-size characters
//	- image MUST be in ASCII order!
//	- image can be missing characters, as long as there is space reserved
//	- image MUST have a size power-of-2 (e.g. 64, 128, 256, 512)
class BitmapFont
{
public:
	/**********************************************************/
	// Constructor & Destructor
	BitmapFont(void) = default;
	~BitmapFont(void) = default;


	/**********************************************************/
	// Initialize & Terminate
	void Initialize(const char* _filename);	// should have parameters
	void Terminate(void);


	/**********************************************************/
	// Draw
	void Draw(const char* output, SGD::Point position,
		float scale, SGD::Color color) const;

	void Draw(const wchar_t* output, SGD::Point position,
		float scale, SGD::Color color) const;

	float Center(const char* output) const;

private:
	/**********************************************************/
	// image
	SGD::HTexture	m_hImage = SGD::INVALID_HANDLE;

	struct Letter
	{
		int letterID;
		int x;
		int y;
		int width;
		int height;
		int xoffset;
		int yoffset;
		int space;
	};

	std::vector<Letter*> letterArr;

	bool			m_bOnlyUppercase = false;
};

#endif //BITMAPFONT_H
