#pragma once
#include <HAPI_lib.h>
#include <string>
#include <unordered_map>
#include "Sprite.h"

using namespace HAPISPACE;

class Sprite;

class Visualisation
{
private:
	int m_width;
	int m_height;
	BYTE* m_screen{ nullptr };
	std::unordered_map<std::string, Sprite*> m_spritemap;
	
public:

	void Initialise(int width, int height);
	void ClearToColourRGB(int Colour[4]);
	void ClearToColour(HAPI_TColour Colour);
	void DrawStars();
	bool LoadSprite(const std::string& filename, const std::string& spritename);
	bool DrawSprite(const std::string spritename, int posx, int posy, bool alpha);
	int getHeight() { return m_height; };
	int getWidth() { return m_width; };

};