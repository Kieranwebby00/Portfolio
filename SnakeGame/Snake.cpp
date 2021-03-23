#include "Snake.h"
#include "Game.h"
#include <list>
#include <iostream>

extern int Width;
extern int Height;

//renders the snakes
void Snake::Render(sf::RenderWindow& window)
{
	//ensures only alive snakes are displayed
	if (!Dead)
	{
		//displays the snakes head
		sf::RectangleShape Snake(position);
		Snake.setPosition(position);
		Snake.setSize(sf::Vector2f(25, 25));
		
		//if the snakes is in gobblemode then its changed to cyan
		if (GobbleMode) { Snake.setFillColor(sf::Color::Cyan); }
		else { Snake.setFillColor(sf::Color::Green); }

		window.draw(Snake);
		//std::cout << "Snake x:" << position.x << " y:" << position.y << " Size:" << Size << std::endl;

		//displays the snakes tail looping through each segment
		for (sf::Vector2f TailPos : Tail)
		{
			sf::RectangleShape Tail(TailPos);
			Tail.setPosition(TailPos);
			Tail.setSize(sf::Vector2f(25, 25));
			Tail.setFillColor(sf::Color::Green);
			//if the snakes is in gobblemode then its changed to cyan
			if (GobbleMode) { Tail.setFillColor(sf::Color::Cyan); }
			else { Tail.setFillColor(sf::Color::Green); }
			window.draw(Tail);
		}
	}
	else
	{
		//std::cout << "Snake Dead" << std::endl;
	}
};

void Snake::SnakeCollision(Snake& snake)
{
	//checks for collisions with the snakes own tails skipping the first check
	bool skip =  false;
	for (auto& Tail1 : Tail)
	{
		if (skip)
		{
			if (Tail.front() == Tail1) { Dead = true; }
		}
		skip = true;
		
	}

	if (!snake.Dead)
	{
		//checks for head on head collision with another snake (second snake supplied through a parameter)
		if (snake.position.x == position.x && snake.position.y == position.y)
		{
			Dead = true;
			snake.Dead = true;
		}
		//if the snake is in gobble mode then instead of killing the snake the snake eats otherssegments
		else if (GobbleMode)
		{
			bool Gobbled = false;
			int count = 0;
			//loops through each tail segment of the second snake checking for a collision with the current snakes head
			for (sf::Vector2f TailSegment : snake.Tail)
			{
				if (TailSegment.x == position.x && TailSegment.y == position.y)
				{
					Gobbled = true;
				}
				//counts each segment past the gobbled segment
				if (Gobbled)
				{
					count++;

				}
			}
			//shrinks the gobble snake to the correct size
			for (int i=0; i < count; i++)
			{
				snake.Tail.pop_back();
			}
			//grows the current snake the correct amount
			Grow(count);
		}


		// checks for normal collisions that kill the current snake
		else
		{
			for (sf::Vector2f TailSegment : snake.Tail)
			{
				if (TailSegment.x == position.x && TailSegment.y == position.y)
				{
					Dead = true;
				}

			}
		}
	}

}


//changes the snakes direction depending on the key pressed
void Snake::PlayerDirection(eDirection direction)
{
	if (direction == eDirection::eLeft && CurrentDirection != eDirection::eRight)
		CurrentDirection = direction;
	if (direction == eDirection::eUp  && CurrentDirection != eDirection::eDown)
		CurrentDirection = direction;
	if (direction == eDirection::eRight && CurrentDirection != eDirection::eLeft)
		CurrentDirection = direction;
	if (direction == eDirection::eDown && CurrentDirection != eDirection::eUp)
		CurrentDirection = direction;
};


//manually sets the snakes direction used for the AI snakes
void Snake::SetAiDirection(eDirection direction)
{
	CurrentDirection = direction;
}


//steps the current snake forward 25pixels dependign on the directions
void Snake::Step()
{
	if (CurrentDirection == eDirection::eLeft) {
		//steps in the direction
		position.x -= 25;
		//kills the snake if they collide with the walls
		if (position.x < 25)
			Dead = true;
	}
	if (CurrentDirection == eDirection::eRight) {
		position.x += 25;
		if (position.x > Width - 25)
			Dead = true;
	}
	if (CurrentDirection == eDirection::eUp) {
		position.y -= 25;
		if (position.y < 25)
			Dead = true;
	}
	if (CurrentDirection == eDirection::eDown) {
		position.y += 25;
		if (position.y > Height - 25)
			Dead = true;
	}
	//moves the tail with the head
	Tail.push_front(position);
	if (Size == 0)
		Tail.pop_back();
	else
		Size--;
}

//both grows the snake and sets gobble mode
void Snake::Grow(int ammount)
{
	if (!Dead)
	{
		//checks if the food consumed was gobbble food
		if (ammount == 0)
		{
			GobbleMode = true;
			//std::cout << "GOBBLEGOBBLE!\na";
		}
		else {
			//increases the snakes size and score depending on the parameter
			Size += ammount;
			Score += ammount;
		}
	}

};


//randomly disables gobble mode 
void Snake::GobbleModeToggle()
{
	if (GobbleMode)
	{
		if (rand() % 50 == 0) {
			GobbleMode = false;
		}
	}
}







