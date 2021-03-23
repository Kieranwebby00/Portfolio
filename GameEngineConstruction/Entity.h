#pragma once
#include <string>
#include "Visualisation.h"
#include "Vec2.h"
#include "World.h"

enum class ESide
{
	eNeutral,
	ePlayer,
	eEnemy,
	eBullet,
};


class Entity
{
protected:
	int m_screenw = 752;
	int m_screenh = 800;
	int m_height = 0;
	int m_width = 0;
	Vec2 m_pos;
	std::string m_name;
	int m_health{ 1 };
	bool m_alive{ true };
	float m_speed = 0.5f;
	bool Shot = false;
	float counter = 10;
public:
	Entity(std::string name) : m_name(name) {}
	virtual void Update(Visualisation& vis, World* game)=0;
	virtual void Render(Visualisation &vis)=0;
	virtual void Initialise(Vec2 startPos, Vec2 direction)=0;
	virtual ESide GetSide() const = 0;
	void setStart(int x, int y, int width, int height);
	virtual void Collided(Entity& other, World* game) = 0;
	bool CheckCollision(Entity& other);
	int getX() { return m_pos.x; };
	int getY() { return m_pos.y; };
	bool isAlive() { return m_alive;}
	void ToggleAlive() { m_alive = !m_alive; }
	bool Cooldown(int time);
};