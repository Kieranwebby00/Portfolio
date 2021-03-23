#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	int m_lives = 5;
	float m_speed = 1;
	int Timer = 100;

public:
	Player(std::string name) : Entity(name) {}
	void Update(Visualisation& vis, World* game) override;
	void Collided(Entity& other, World* game) override;
	void Render(Visualisation& vis) override;
	void Initialise(Vec2 startPos, Vec2 Direction) override;
	ESide GetSide() const override { return ESide::ePlayer; }
};

