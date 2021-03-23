#include "Framework.h"

void Framework::Initialize(int width, int height)
{
	m_width = width;
	m_height = height;

}

void Framework::Render(sf::RenderWindow& window, int x, int y, int colour)
{
	m_position.x = x;
	m_position.y = y;
	//creates and displays a square
	sf::RectangleShape Square(m_position);
	Square.setPosition(m_position);
	Square.setSize(m_size);
	if(colour == 1)
		Square.setFillColor(sf::Color::Black);
	if (colour == 2)
		Square.setFillColor(sf::Color::White);
	if (colour == 3)
		Square.setFillColor(sf::Color::Red);
	if (colour == 4)
		Square.setFillColor(sf::Color::Black);

	// draw our shape to the window
	window.draw(Square);

}
