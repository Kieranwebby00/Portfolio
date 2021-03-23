#include "Food.h"
#include <iostream>


//function that renders the food
void Food::Render(sf::RenderWindow& window)
{
	//checks if the food is in gobble mode since it is rendered with different values to the rest
	if (!GobbleMode)
	{
		if (visible)
		{
			//sets the size of the food giving varied scores and sizes
			sf::CircleShape Food((FoodSize * 5) / 2);
			Food.setPosition(FoodPos);
			Food.setFillColor(sf::Color::Red);
			window.draw(Food);
		}
	}
	//if the food is in gobble mode then its rendered in blue with no size so players dont gain score for entering gobble mode.
	else {
		FoodSize = 0;
		sf::CircleShape Food(12.5);
		Food.setPosition(FoodPos);
		Food.setFillColor(sf::Color::Cyan);
		window.draw(Food);
	}

	
	//std::cout << "Food x:" << FoodPos.x << " y:" << FoodPos.y << " Size:" << FoodSize << std::endl;
}

//sets the x,y position of the food
void Food::SetPosition(int x, int y)
{
	FoodPos.x = x;
	FoodPos.y = y;
}


//randomly sets the size of the food between 1-5
void Food::SetSize()
{
	FoodSize = (rand() % 5 + 1);
}

//toggles the foods visibility when spawning and consuming them
void Food::ToggleVisibility() {visible = !visible;};