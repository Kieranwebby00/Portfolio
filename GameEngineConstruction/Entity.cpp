#include "Entity.h"
#include "Rectangles.h"


void Entity::setStart(int x, int y, int width, int height)
{
	m_pos.x = x;
	m_pos.y = y;
	m_width = width;
	m_height = height;
}

bool Entity::CheckCollision(Entity& other)
{
	if (m_pos.x < other.m_pos.x + other.m_width && m_pos.x + m_width > other.m_pos.x
		&& m_pos.y < other.m_pos.y + other.m_height && m_pos.y + m_height > other.m_pos.y)
	{
		return true;
	}
	return false;
}

bool Entity::Cooldown(int time)
{
	if (Shot) {
		counter -= 1;
		if (counter <= 0)
		{
			counter = time;
			Shot = false;
			return false;
		}
	}
	return true;
}

