#pragma once
#include "Entity.h"
#include "Vec2.h"
class Bullet : public Entity
{
private:
	Vec2 m_direction;
	int m_damage = 1;
	float m_speed = 2;
	ESide Parent;
	
public:
	Bullet(std::string name) : Entity(name) { m_alive = false; }
	void Update(Visualisation& vis, World* game) override;
	void Render(Visualisation& vis) override;
	void Collided(Entity& other, World* game) override;
	void Initialise(Vec2 startPos, Vec2 Direction) override;
	ESide GetSide() const override { return ESide::eBullet; }
};




