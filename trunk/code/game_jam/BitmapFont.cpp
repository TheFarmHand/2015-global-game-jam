/***************************************************************
|	File:		BitmapFont.cpp
|	Author:		Nick Dalton
|	Course:		SGD 1407
|	Purpose:	BitmapFont class draws text using an image
|				of fixed-size character glyphs
***************************************************************/

#include "BitmapFont.h"
#include "TinyXML/tinyxml.h"

#include "WRAPPERS/SGD_GraphicsManager.h"
#include "WRAPPERS/SGD_Geometry.h"

#include <ctype.h>
#include <cassert>


/**************************************************************/
// Initialize
//	- configure the font for "SGD_Font_Glow.png"
//	- probably should have parameters / config file
void BitmapFont::Initialize(const char* _filename)
{
	// Load the image
	m_hImage = SGD::GraphicsManager::GetInstance()->LoadTexture(L"Assets/Font_0.png");

	int charCount = 0;

	TiXmlDocument font;

	if (font.LoadFile(_filename) == false)
		return;

	TiXmlElement* root = font.RootElement();

	if (root == nullptr)
		return;

	TiXmlElement* chars = root->FirstChildElement("chars");
	chars->Attribute("count", &charCount);

	chars = chars->FirstChildElement("char");

	for (int i = 0; i < charCount; i++)
	{
		Letter* tempLetter = new Letter;

		chars->Attribute("id", &tempLetter->letterID);
		chars->Attribute("x", &tempLetter->x);
		chars->Attribute("y", &tempLetter->y);
		chars->Attribute("width", &tempLetter->width);
		chars->Attribute("height", &tempLetter->height);
		chars->Attribute("xoffset", &tempLetter->xoffset);
		chars->Attribute("yoffset", &tempLetter->yoffset);
		chars->Attribute("xadvance", &tempLetter->space);

		letterArr.push_back(tempLetter);
		chars = chars->NextSiblingElement("char");
	}



}


/**************************************************************/
// Terminate
//	- clean up resources
void BitmapFont::Terminate(void)
{
	// Unload the image
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hImage);

	for (unsigned int i = 0; i < letterArr.size(); i++)
		delete letterArr[i];

	letterArr.clear();
}


/**************************************************************/
// Draw
//	- draw the text one character at a time,
//	  using the Cell Algorithm to calculate the source rect
void BitmapFont::Draw(const char* output, SGD::Point position,
	float scale, SGD::Color color) const
{
	// Validate the image
	assert(m_hImage != SGD::INVALID_HANDLE
		&& "BitmapFont::Draw - image was not loaded");

	// Validate the parameter
	assert(output != nullptr
		&& "BitmapFont::Draw - string cannot be null");

	int spaceWidth = 8;


	// Is this string invisible?
	if (output[0] == '\0'			// string is empty?
		|| scale == 0.0f			// scale is invisible?
		|| color.alpha == 0)		// color is invisible?
		return;


	// Store the starting X position for newlines
	float colStart = position.x;

	// Iterate through the characters in the string
	for (int i = 0; output[i]; i++)
	{
		// Get the current character
		char ch = output[i];


		// Check for whitespace
		if (ch == ' ')
		{
			// Move to the next position
			position.x += spaceWidth * scale;
			continue;
		}
		else if (ch == '\n')
		{
			// Move to the next row
			position.y += 32 * scale;
			position.x = colStart;
			continue;
		}
		else if (ch == '\t')
		{
			// Calculate the number of pixels from the start
			float pixels = position.x - colStart;

			// Calculate the number of characters from the start
			int chars = int(pixels / (spaceWidth * scale));

			// Calculate the number of characters to add
			// to get a 4-space alignment
			int spaces = 4 - (chars % 4);


			// Move to the next position
			position.x += spaces * (spaceWidth * scale);
			continue;
		}


		// Convert to uppercase?
		if (m_bOnlyUppercase == true)
			ch = toupper(ch);


		// Calculate the tile ID for this character
		unsigned int id = ch - 32;

		if (id < 0 || id > letterArr.size() - 1)
			continue;

		// Calculate the source rect for that glyph
		SGD::Rectangle cell;
		cell.left = (float)letterArr[id]->x;
		cell.top = (float)letterArr[id]->y;
		cell.right = (float)letterArr[id]->width + cell.left;
		cell.bottom = (float)letterArr[id]->height + cell.top;

		SGD::Point actualPosition = position;
		actualPosition.x -= letterArr[id]->xoffset * scale;
		actualPosition.y += letterArr[id]->yoffset * scale;

		// Draw the character
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(
			m_hImage, actualPosition,
			cell, 0.0f, {},
			color, { scale, scale });


		// Move to the next position
		position.x += (int)(letterArr[id]->space * scale);
	}
}


/**************************************************************/
// Draw
//	- draw the text one character at a time,
//	  using the Cell Algorithm to calculate the source rect
void BitmapFont::Draw(const wchar_t* output, SGD::Point position,
	float scale, SGD::Color color) const
{
	// Validate the image
	assert(m_hImage != SGD::INVALID_HANDLE
		&& "BitmapFont::Draw - image was not loaded");

	// Validate the parameter
	assert(output != nullptr
		&& "BitmapFont::Draw - string cannot be null");

	int spaceWidth = 8;


	// Is this string invisible?
	if (output[0] == '\0'			// string is empty?
		|| scale == 0.0f			// scale is invisible?
		|| color.alpha == 0)		// color is invisible?
		return;


	// Store the starting X position for newlines
	float colStart = position.x;

	// Iterate through the characters in the string
	for (int i = 0; output[i]; i++)
	{
		// Get the current character
		wchar_t ch = output[i];


		// Check for whitespace
		if (ch == ' ')
		{
			// Move to the next position
			position.x += spaceWidth * scale;
			continue;
		}
		else if (ch == '\n')
		{
			// Move to the next row
			position.y += 32 * scale;
			position.x = colStart;
			continue;
		}
		else if (ch == '\t')
		{
			// Move to the next position
			position.x += (spaceWidth * 4) * scale;
			continue;
		}


		// Convert to uppercase?
		if (m_bOnlyUppercase == true)
			ch = toupper(ch);


		// Calculate the tile ID for this character
		unsigned int id = ch - 32;

		if (id < 0 || id > letterArr.size() - 1)
			continue;

		// Calculate the source rect for that glyph
		SGD::Rectangle cell;
		cell.left = (float)letterArr[id]->x;
		cell.top = (float)letterArr[id]->y;
		cell.right = (float)letterArr[id]->width + cell.left;
		cell.bottom = (float)letterArr[id]->height + cell.top;

		SGD::Point actualPosition = position;
		actualPosition.x -= letterArr[id]->xoffset * scale;
		actualPosition.y += letterArr[id]->yoffset * scale;

		// Draw the character
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(
			m_hImage, actualPosition,
			cell, 0.0f, {},
			color, { scale, scale });


		// Move to the next position
		position.x += (int)(letterArr[id]->space * scale);
	}
}

float BitmapFont::Center(const char* output) const
{
	float pixelLength = 0.0f;

	for (int i = 0; output[i] && output[i] != '\n'; i++)
	{

		if (output[i] == ' ')
			pixelLength += 8.0f;
		else if (output[i] == '\t')
			pixelLength += 32.0f;
		else
			pixelLength += letterArr[output[i] - 32]->width;
	}
	pixelLength *= 0.5f;

	return pixelLength;

}