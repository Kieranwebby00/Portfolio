#pragma once
#include <vector>
#include "Vec2.h"

class Entity;
class Visualisation;



class World 
{
private:
	std::vector<Entity*> m_Entities;
	Visualisation *m_vis{nullptr};
	int m_screenw = 0;
	int m_screenh = 0;

	size_t m_BulletStart{ 0 };
	size_t m_EnemyStart{ 0 };
public:
	bool LoadLevel();
	void Update();
	bool Initialise(int width, int height);
	void FireBullet(Vec2 StartPos, Vec2 direction);
	void NewEnemy(Vec2 StartPos, float dx, float dy);
};
