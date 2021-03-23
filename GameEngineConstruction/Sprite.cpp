#include "Sprite.h"

bool Sprite::LoadTexture(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &m_texture, m_texturewidth, m_textureheight)) {
		std::cout << "FILE NOT FOUND1" << std::endl;
		return false;
	}
	else
		return true;
}

void Sprite::FastBlit(BYTE* screen, int screenwidth, int screenheight, int x, int y)
{
	while (x + m_texturewidth > screenwidth) { x--; }
	while (y + m_textureheight > screenheight) { y--; }
	screen = screen + (x + y * screenwidth) * 4;
	BYTE* Temp = m_texture;
	for (int y = 0; y < m_textureheight; y++) {
		memcpy(screen, Temp, m_texturewidth * 4);
		Temp += m_texturewidth * 4;
		screen += screenwidth * 4;
	}
}

void Sprite::AlphaBlit(BYTE* screen, int screenwidth, int screenheight, int x, int y)
{
	while (x + m_texturewidth > screenwidth) { x--; }
	while (y + m_textureheight > screenheight) { y--; }
	BYTE* sStart = screen + (x + y * screenwidth) * 4;
	BYTE* tStart = { m_texture };
	for (int x = 0; x < m_texturewidth;x++) {
		for (int y = 0; y < m_textureheight;y++) {
			BYTE r = tStart[0];
			BYTE g = tStart[1];
			BYTE b = tStart[2];
			BYTE a = tStart[3];
			float alpha = a / 255.0f;
			if (alpha == 255.0f) {
				memcpy(sStart, tStart, 4);
			}
			else {
				sStart[0] = alpha * r + sStart[0] * (1.0f - alpha);
				sStart[1] = alpha * g + sStart[1] * (1.0f - alpha);
				sStart[2] = alpha * b + sStart[2] * (1.0f - alpha);
				sStart += 4;
				tStart += 4;
			}
		}
		sStart += screenwidth * 4 - m_texturewidth * 4;
	}
}

void Sprite::ClippingBlit(BYTE* screen, int screenwidth, int screenheight, int x, int y)
{
	Rectangle ScreenRectangle(0, screenwidth,0, screenheight);
	Rectangle TextureRectangle(0, m_texturewidth,0, m_textureheight);

	TextureRectangle.Translate(x, y);
	TextureRectangle.ClipScreen(ScreenRectangle);
	TextureRectangle.Translate(-x, -y);

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	BYTE* sStart = screen + (x + y * screenwidth) * 4;
	BYTE* tStart =  m_texture + (TextureRectangle.m_left + TextureRectangle.m_top * m_texturewidth) * 4;


	for (int y = 0; y < TextureRectangle.height();y++) {
		for (int x = 0; x < TextureRectangle.width();x++) {
			BYTE r = tStart[0];
			BYTE g = tStart[1];
			BYTE b = tStart[2];
			BYTE a = tStart[3];
			float alpha = a / 255.0f;
			if (alpha == 255.0f) {
				memcpy(sStart, tStart, 4);
			}
			else {
				sStart[0] = alpha * r + sStart[0] * (1.0f - alpha);
				sStart[1] = alpha * g + sStart[1] * (1.0f - alpha);
				sStart[2] = alpha * b + sStart[2] * (1.0f - alpha);
				sStart += 4;
				tStart += 4;
			}
		}
		sStart += screenwidth * 4 - TextureRectangle.width() * 4;
		tStart += m_texturewidth * 4 - TextureRectangle.width() * 4;
	}

}


Sprite::~Sprite()
{
	delete[]m_texture;
}
