#pragma once
#include "Entity.h"
     
class Enemy : public Entity
{
private:
	int dx = rand() %2 -1;
	int dy = 1;
public:
	Enemy(std::string name) : Entity(name) { m_alive = true; };
	void Update(Visualisation& vis, World* game) override;
	void Render(Visualisation& vis) override;
	void Collided(Entity& other, World* game) override;
	void Initialise(Vec2 startPos, Vec2 Direction) override;
	ESide GetSide() const override { return ESide::eEnemy; }
};