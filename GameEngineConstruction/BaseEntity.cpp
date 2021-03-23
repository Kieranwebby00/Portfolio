#include "BaseEntity.h"

void BaseEntity::Update(Visualisation& vis, World* game)
{
};

void BaseEntity::Render(Visualisation& vis)
{
	vis.DrawSprite(m_name, m_pos.x, m_pos.y, false);
}
void BaseEntity::Collided(Entity& other, World* game)
{
	return;
}
void BaseEntity::Initialise(Vec2 startPos, Vec2 Direction)
{
};
