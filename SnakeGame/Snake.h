#pragma once
#include <SFML/Graphics.hpp>
#include <list>
enum class eDirection
{
	eUp,
	eDown,
	eRight,
	eLeft
};

class Snake
{
public:
	void Render(sf::RenderWindow& window);
	void PlayerDirection(eDirection direction);
	void Step();
	void Grow(int ammount);
	void SetAiDirection(eDirection direction);
	void GobbleModeToggle();
	void SnakeCollision(Snake& snake);

	sf::Vector2f position;
	eDirection CurrentDirection;
	std::list<sf::Vector2f> Tail;
	int Target;
	bool Dead = false;
	int Size = 0;
	int Score = 0;
	bool GobbleMode = false;
};

