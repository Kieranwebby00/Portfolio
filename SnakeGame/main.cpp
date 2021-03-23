#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

//sets the variables used for timing and window size
int timeDelayMS = 100;
int Width{ 800 };
int Height{ 800 };

int main()
{
	//displays the menu that accepts and input and runs the chosen option with simple error checking
	int option = 1;
	while (option != 0) {
		std::cout<< "New Game                (1) \n" << "Quit                    (0) \n" << "Please Choose An Option: ";
		std::cin >> option;
		if (option == 1) {
			Game NewSnakeGame;
			NewSnakeGame.NewGame();
		}
		else
			std::cout << "ERROR please try again. \n"; 
	}
	return 0;
}

