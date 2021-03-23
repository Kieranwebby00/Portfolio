//SFML documentation: https://www.sfml-dev.org/learn.php
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Framework.h"
#include "Prims.h"

Framework shape;
Prims Maze;

int width = 1000;
int height = 1000;
constexpr int rows{ 50 };
constexpr int columns{ 50 };
int size = 20; 
int maze[rows][columns];


int main()
{
    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text

	sf::RenderWindow window(sf::VideoMode(width, height), "ICA2 Algorithms");
	shape.Initialize(width, height);
	Maze.Initialize(maze);

    // Main loop that continues until we call window.close()
    while (window.isOpen())
	{
        // Handle any pending SFML events
        sf::Event event;
        while (window.pollEvent(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed:
              window.close();
            break;
            default:
              break;
          }
        }
		//Draws the graphics
		window.clear();
		for (int x = 0; x < rows;x++)
		{
			for (int y = 0; y < columns;y ++)
			{
				shape.Render(window, x*size, y*size, maze[x][y]);
			}
		}
		Maze.Step(maze);
		// Get the window to display its contents
		window.display();
    }
	
    return 0;
}


