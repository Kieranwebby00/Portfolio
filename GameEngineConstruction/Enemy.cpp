#include "Enemy.h"

void Enemy::Update(Visualisation& vis, World* game)
{
	if (m_alive) {
		m_pos.x += dx * m_speed;
		m_pos.y += dy * m_speed;
		if (m_pos.x > m_screenw - m_width) {
			dx = -dx;
			dy = rand() % 2 - 1;
		}
		if (m_pos.x < 0) {
			dx = -dx;
			dy = rand() % 2 - 1;
		}
		if (m_pos.y > m_screenh - m_height) {
			dy = -dy;
			dx = rand() % 2 - 1;
		}
		if (m_pos.y < 0) {
			dy = -dy;
			dx = rand() % 2 - 1;
		}
	}
}

void Enemy::Render(Visualisation& vis)
{
	if(m_alive){
	vis.DrawSprite(m_name, m_pos.x, m_pos.y, true);}
}

void Enemy::Collided(Entity& other, World* game)
{
	if (other.GetSide() == ESide::ePlayer)
	{
		std::cout << "player" << std::endl;
		m_alive = false;
		game->NewEnemy(Vec2{ float(rand() % (m_screenw / 2 - 58) + 1), 0 }, float(rand() % 2 - 1), 1);
	}

	if (other.GetSide() == ESide::eBullet)
	{
		std::cout << "bullet" << std::endl;
		m_alive = false;
		game->NewEnemy(Vec2{ float(rand() % (m_screenw/2 - 58) + 1), 0 }, float(rand() % 2 - 1), 1);
	}

}

void Enemy::Initialise(Vec2 startPos, Vec2 Direction)
{
	m_alive = true;
	m_pos = startPos;
	int dy = Direction.x;
	int dx = Direction.y;
}


