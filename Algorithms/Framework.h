#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class Framework
{
private:
	bool m_visible = true;
	sf::Vector2f m_size{ 18,18 };
	sf::Vector2f m_position{0,0};
	int m_width=0;
	int m_height=0;
public:
	void Initialize(int width, int height);
	void Render(sf::RenderWindow& window, int x, int y, int colour);
};

