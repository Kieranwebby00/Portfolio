#pragma once
#include <SFML/Graphics.hpp>

class Food
{
public:
	bool visible = false;
	void ToggleVisibility();
	void Render(sf::RenderWindow& window);
	void SetPosition(int x,int y);
	void SetSize();
	sf::Vector2f FoodPos;
	int FoodSize{ 1 };
	bool GobbleMode = false;
};