#include "Bullet.h"

void Bullet::Update(Visualisation& vis, World* game)
{
	if (m_alive)
	{
		m_pos.x += m_direction.x *m_speed;
		m_pos.y += m_direction.y * m_speed;
		if (m_pos.x > m_screenh || m_pos.x < 0 || m_pos.y > m_screenw || m_pos.y < 0) {
			m_alive = false;
		}
	}
}

void Bullet::Render(Visualisation& vis)
{
	if (m_alive)
	{
		vis.DrawSprite(m_name, m_pos.x, m_pos.y, true);
	}
}

void Bullet::Initialise(Vec2 startPos, Vec2 direction)
{
	m_alive = true;
	m_pos = startPos;
	m_direction = direction;

}

void Bullet::Collided(Entity& other, World* game)
{
}