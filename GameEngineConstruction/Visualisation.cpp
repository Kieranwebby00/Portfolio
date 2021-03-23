#include "Visualisation.h"
#include "Sprite.h"

void Visualisation::Initialise(int swidth, int sheight)
{
	if (!HAPI.Initialise(swidth, sheight, "Window")) {
		std::cout << "Screen Initialisation Failed. " << std::endl;
		return;
	}
	HAPI.SetShowFPS(true);
	BYTE* screen = HAPI.GetScreenPointer();
	m_width = swidth;
	m_height = sheight;
	m_screen = screen;
	std::cout << "Screen Initialised. " << std::endl;
}

void Visualisation::ClearToColourRGB(int Colour[4])
{
	for (int i = 0; i < m_width * m_height * 4; i += 4) {
		m_screen[i] = Colour[0];//red	
		m_screen[i + 1] = Colour[1];//green
		m_screen[i + 2] = Colour[2];//blue
		m_screen[i + 3] = Colour[3];//alpha
	}
};

void Visualisation::ClearToColour(HAPI_TColour Colour)
{
	for (int i = 0; i < m_width * m_height; i++) {
		memcpy(m_screen + i * 4, &Colour, 4);
	}
};

//Star Structure and variables
bool Start = true;
int eyeDistance = 100;
const int NumberofStars = 1000;
struct Star {
	int x = 0;
	int y = 0;
	int z = 0;
	int size = 0;
};
Star Stars[1000];

void Visualisation::DrawStars()
{
	HAPI_TColour StarColour(HAPI_TColour::WHITE);
	if (Start) {

		//Sets random x,y,z for each star
		for (int i = 0; i < NumberofStars; i++) {
			Stars[i].x = rand() % m_width;
			Stars[i].y = rand() % m_height;
			Stars[i].z = rand() % 1000 + 1;
			Stars[i].size = 0;
		}
		Start = false;
	};

	//draws stars
	for (int i = 0; i < NumberofStars; i++) {

		int Sx = ((eyeDistance * (Stars[i].x - m_width / 2)) / (Stars[i].z + eyeDistance)) + m_width / 2;
		int Sy = ((eyeDistance * (Stars[i].y - m_height / 2)) / (Stars[i].z + eyeDistance)) + m_height / 2;

		int offset = (Sx + Sy * m_width) * 4;
		//std::cout << Sx << Sy << std::endl;
		memcpy(m_screen + offset, &StarColour, 4);


		//increse the size of the stars
		for (int y = Sy - Stars[i].size; y < Sy + Stars[i].size; y++)
		{
			for (int x = Sx - Stars[i].size; x < Sx + Stars[i].size; x++)
			{
				int offset = (x + y * m_width) * 4;
				memcpy(m_screen + offset, &StarColour, 4);
			}
		}

		//move the stars
		Stars[i].z--;
		Stars[i].size = 2 - (Stars[i].z / eyeDistance);

		//reset the stars
		if (Stars[i].z <= 1) {
			Stars[i].x = rand() % m_width;
			Stars[i].y = rand() % m_height;
			Stars[i].z = 1000;
			Stars[i].size = 0;
		}
	}

	/*const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	if (keyData.scanCode['E']) {
		eyeDistance++;
		if (eyeDistance > 100) { eyeDistance = 100; };
	}
	if (keyData.scanCode['Q']) {
		eyeDistance--;
		if (eyeDistance <= 1) { eyeDistance = 1; };
	}*/
}


bool Visualisation::LoadSprite(const std::string& filename, const std::string& spritename)
{
	Sprite* tempSprite = new Sprite;
	if (!tempSprite->LoadTexture(filename)) {
		delete tempSprite;
		return false;
	};
	m_spritemap[spritename] = tempSprite;
	return true;
}


bool Visualisation::DrawSprite(const std::string spritename, int posx, int posy, bool alpha)
{
	if (m_spritemap.find(spritename) == m_spritemap.end()) {
		std::cout << "SPRITE NOT FOUND" << std::endl;
		return false;
	}
	if(alpha)
		m_spritemap[spritename]->ClippingBlit(m_screen, m_width, m_height, posx, posy);
	else
		m_spritemap[spritename]->FastBlit(m_screen, m_width, m_height, posx, posy);
	return true;
}







