#pragma once
#include <HAPI_lib.h>
#include "Rectangles.h"
using namespace HAPISPACE;

class Sprite
{
private:
	int m_texturewidth =0;
	int m_textureheight=0;
	BYTE* m_texture{ nullptr };

public:
	bool LoadTexture(const std::string& filename);
	void FastBlit(BYTE* screen, int screenwidth, int screenheight, int x, int y);
	void AlphaBlit(BYTE* screen, int screenwidth, int screenheight, int x, int y);
	Sprite::~Sprite();
	void Sprite::ClippingBlit(BYTE* screen, int screenwidth, int screenheight, int x, int y);

};

