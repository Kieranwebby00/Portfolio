#pragma once
#include "Food.h"
#include "Snake.h"

class Game
{
public:
	void NewGame();
	void SpawnFood(bool Gobble);
	void FoodCollision(Snake& snake);
	void MoveAi(Snake& snake, int num);

private:
	Food FoodArray[5];
};