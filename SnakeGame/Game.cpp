#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <string>


using namespace std::this_thread;
using namespace std::chrono;

extern int timeDelayMS;
extern int Width;
extern int Height;
int VisibleFood = 0;


//Source https://stackoverflow.com/questions/3407012/c-rounding-up-to-the-nearest-multiple-of-a-number 
//function use to align food
int roundUp(int numToRound)
{
	int remainder = numToRound % 25;
	if (remainder == 0)
		return numToRound;
	return numToRound + 25 - remainder;
}

void Game::SpawnFood(bool Gobble)
{

	// Spawns food in empty square
	for (int i = 0; i < 5; i++)
	{
		if (FoodArray[i].visible == false)
		{
				//while loop used to check for a random empty spawning place for the food
				bool FoodSpawned = false;
				while (!FoodSpawned)
				{
					//choses two random coords with in the area rounded to the closest 25pixels
					int Tempx = roundUp(rand() % Width + 1);
					int Tempy = roundUp(rand() % Height + 1);
					for (int j = 0; j < 5; j++)
					{
						//makes sure there are no other food in the choses coords
						if (Tempx == 0 || Tempx == Width || Tempy == 0 || Tempy == Width)
							FoodSpawned = false;
						//if the area is free the food is placed there and given a size
						else if (FoodArray[j].FoodPos.x != Tempx && FoodArray[j].FoodPos.y != Tempy)
						{
							FoodArray[i].SetPosition(Tempx, Tempy);
							FoodArray[i].SetSize();
							if (Gobble) {
								FoodArray[i].GobbleMode = true;
							}
							FoodSpawned = true;
						}
					}
				}
				//spawns the food and counts the amount of visible food
				FoodArray[i].ToggleVisibility();
				VisibleFood++;
				break;
		}
	};
}

void Game::FoodCollision(Snake& snake)
{
	//Detects food collisions
	for (int i = 0; i < 5; i++)
	{
		//makes sure that only visible food is checked 
		if (FoodArray[i].visible)
		{
			//compares snakes pos with the foods pos
			if (FoodArray[i].FoodPos.x == snake.position.x && FoodArray[i].FoodPos.y == snake.position.y)
			{
				//on collisions visible food is updated and the foods visibility is toggled
				FoodArray[i].ToggleVisibility();
				VisibleFood--;
				//updates the snakes size and score depending on the food consumed
				snake.Grow(FoodArray[i].FoodSize);
				//std::cout << "FoodSize: " << FoodArray[i].FoodSize << std::endl;
				//ensures at least one food is available at all times
				if (FoodArray[i].FoodSize == 0) {
					if (VisibleFood < 1) { SpawnFood(true); }
				}
				
				else {
					SpawnFood(false);//makes sure food is spawned looping this function untill true
				}

			}
		}
	}
}




void Game::MoveAi(Snake& snake, int num)
{
	if (!snake.Dead)
	{
		//old AI loop that moved the snake to the first food at all times which caused the snake to run into walls
		
		/*
		for (int i = 0; i < 5; i++)
		{
			if (FoodArray[i].visible == true)
			{
				if (FoodArray[i].FoodPos.x > snake.position.x) { snake.PlayerDirection(eDirection::eRight); break; }
				if (FoodArray[i].FoodPos.x < snake.position.x) { snake.PlayerDirection(eDirection::eLeft); break; }
				if (FoodArray[i].FoodPos.y < snake.position.y) { snake.PlayerDirection(eDirection::eUp); break; }
				if (FoodArray[i].FoodPos.y > snake.position.y) { snake.PlayerDirection(eDirection::eDown); break; }
			}
		}
		*/

		//makes sure the target alocated to a snake is visible 
		while (FoodArray[num].visible == false)
		{
			//if the target isnt available the target changes
			num++;
			if (num == 5) num = 0;
		}


		//moves the snake to the target while also detecting for collisions with the walls (can however cause some issues when in the corners)
		if (FoodArray[num].FoodPos.x > snake.position.x) 
		{ 
			if (snake.CurrentDirection == eDirection::eLeft)
				snake.PlayerDirection(eDirection::eDown);
			else
				snake.PlayerDirection(eDirection::eRight);
		}

		else if (FoodArray[num].FoodPos.x < snake.position.x)
		{
			if (snake.CurrentDirection == eDirection::eRight)
				snake.PlayerDirection(eDirection::eUp);
			else
				snake.PlayerDirection(eDirection::eLeft);
		}

		else if (FoodArray[num].FoodPos.y < snake.position.y) 
		{
			if (snake.CurrentDirection == eDirection::eDown)
				snake.PlayerDirection(eDirection::eRight);
			else
				snake.PlayerDirection(eDirection::eUp);
		}

		else if (FoodArray[num].FoodPos.y > snake.position.y) 
		{
			if (snake.CurrentDirection == eDirection::eUp)
				snake.PlayerDirection(eDirection::eLeft);
			else
				snake.PlayerDirection(eDirection::eDown);
		}
	}
	
}

void Game::NewGame()
{
	
	//sets the seed, creats the bool used for the game loop and creats the game window
	srand(time(NULL));
	bool GameOver = false;
	sf::RenderWindow Window(sf::VideoMode(Width+25, Height+25), "SnakeGame");
	
	//creates the white walls
	sf::RectangleShape OuterWall(sf::Vector2f(0,0));
	OuterWall.setSize(sf::Vector2f(Width + 25, Height + 25));
	
	//creates the black center to the game
	sf::RectangleShape InnerWall(sf::Vector2f(25, 25));
	InnerWall.setPosition(25, 25);
	InnerWall.setSize(sf::Vector2f(Width-25, Height-25));
	InnerWall.setFillColor(sf::Color::Black);

	std::cout << "\nSnakeGame: Starting \n" << std::endl;

	//creates the players and sets their spawns, which updates with the window size
	Snake player;
	player.position.x = 25;
	player.position.y = 25;

	Snake AIplayer1;
	AIplayer1.position.x = Width - 25;
	AIplayer1.position.y = Height - 25;

	Snake AIplayer2;
	AIplayer2.position.x = 25;
	AIplayer2.position.y = Height - 25;

	Snake AIplayer3;
	AIplayer3.position.x = Width - 25;
	AIplayer3.position.y = 25;

	//spawns food without gobble mode
	SpawnFood(false);
	//spawns food with gobble mode
	SpawnFood(true);
	//sets the count down timer
	int Timer = 900;
	
		//loops the game untill a game over condition is met
		while (!GameOver)
		{
			//checks if the timer is up then ends the game if true
			if (Timer == 0) { GameOver = true; }

			//checks the amount of snakes that are left and ends game if there is 1
			int SnakesLeft = 4;
			if (player.Dead) { SnakesLeft--; }
			if (AIplayer1.Dead) { SnakesLeft--; }
			if (AIplayer2.Dead) { SnakesLeft--; }
			if (AIplayer3.Dead) { SnakesLeft--; }
			if (SnakesLeft < 2) { GameOver = true; }

			
			//displays the walls 
			Window.draw(OuterWall);
			Window.draw(InnerWall);

			//std::cout << "Visible Food: " << VisibleFood << std::endl;

			sf::Event event;
			//Detects keys presses and changes direction where correct
			while (Window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					Window.close();
					break;
				default:
					break;

				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
					case sf::Keyboard::W:
						player.PlayerDirection(eDirection::eUp);
						break;
					case sf::Keyboard::A:
						player.PlayerDirection(eDirection::eLeft);
						break;
					case sf::Keyboard::S:
						player.PlayerDirection(eDirection::eDown);
						break;
					case sf::Keyboard::D:
						player.PlayerDirection(eDirection::eRight);
						break;
					default:
						break;
					}
				}
			}

			//Displays the Visible Food
			for (int i = 0; i < 5; i++)
			{
				if (FoodArray[i].visible == true)
				{
					FoodArray[i].Render(Window);
				}
			};

			//Randomly spawns food
			if (rand() % 10 == 0) { SpawnFood(false); };

			//all the steps required for each player including collision detection between players and food.
			player.Step();
			player.Render(Window);
			player.SnakeCollision(AIplayer1);
			player.SnakeCollision(AIplayer2);
			player.SnakeCollision(AIplayer3);
			FoodCollision(player);
			//attempts to toggle gobble mode
			player.GobbleModeToggle();

			//these steps are repeted for each with only the parameters changing
			MoveAi(AIplayer1,1);
			AIplayer1.Step();
			AIplayer1.Render(Window);
			AIplayer1.SnakeCollision(player);
			AIplayer1.SnakeCollision(AIplayer2);
			AIplayer1.SnakeCollision(AIplayer3);
			FoodCollision(AIplayer1);

			AIplayer1.GobbleModeToggle();

			MoveAi(AIplayer2,2);
			AIplayer2.Step();
			AIplayer2.Render(Window);
			AIplayer2.SnakeCollision(player);
			AIplayer2.SnakeCollision(AIplayer1);
			AIplayer2.SnakeCollision(AIplayer3);
			FoodCollision(AIplayer2);
			AIplayer2.GobbleModeToggle();

			MoveAi(AIplayer3,3);
			AIplayer3.Step();
			AIplayer3.Render(Window);
			AIplayer3.SnakeCollision(player);
			AIplayer3.SnakeCollision(AIplayer2);
			AIplayer3.SnakeCollision(AIplayer1);
			FoodCollision(AIplayer3);
			AIplayer3.GobbleModeToggle();


			//displays the window and waits for a set time
			Window.display();
			sleep_for(milliseconds(timeDelayMS));
			Window.clear();
			//counts down every loop untill game over
			Timer--;
			//std::cout << "Time Left: " << Timer << std::endl; ;

		}
		//once the game is over this sets up the output checking for the highest scoring player 
			std::string Winner = " ";
			int Highest=0;

			if (!player.Dead) {
				if (player.Score >= Highest) {
					Highest = player.Score;
					Winner = "Player 1";
				}
			}
			if (!AIplayer1.Dead) {
				if (AIplayer1.Score >= Highest) {
					Highest = AIplayer1.Score;
					Winner = "Player 2";
				}
			}
			if (!AIplayer2.Dead) {
				if (AIplayer2.Score >= Highest) {
					Highest = AIplayer2.Score;
					Winner = "Player 3";
				}
			}
			if (!AIplayer3.Dead) {
				if (AIplayer3.Score >= Highest) {
					Highest = AIplayer3.Score;
					Winner = "Player 4";
				}
			}
			//if the game ends with all the players dying at the same time its a draw and that message is displayed
			if (Winner == " ") { std::cout << "Game Over its a DRAW!" << std::endl; }
			//otherwise the highest scoring player is declared the winner
			else { std::cout << "The Winner is: " << Winner << " With " << Highest << " Points! \n" << std::endl; }
			std::cout << "SnakeGame: Finished \n" << std::endl;

	
}

