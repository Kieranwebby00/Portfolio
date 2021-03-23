#include <HAPI_lib.h>
#include "Player.h"
#include "Entity.h"

using namespace HAPISPACE;

void Player::Render(Visualisation& vis)
{
	if (m_alive)
	{
		vis.DrawSprite(m_name, m_pos.x, m_pos.y, true);
	}
}
void Player::Initialise(Vec2 startPos, Vec2 Direction)
{};

void Player::Update(Visualisation& vis, World* game)
{
	Cooldown(Timer);
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	if (keyData.scanCode['A']) {
		m_pos.x -= m_speed;
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
	}
	if (keyData.scanCode['D']) {
		m_pos.x += m_speed;
		if(m_pos.x >= vis.getWidth()-m_width)
		{
			m_pos.x = vis.getWidth() - m_width;
		}
	}
	if (keyData.scanCode[' ']) {
		if (!Shot)
		{
			game->FireBullet(Vec2{ m_pos.x + m_width / 2,m_pos.y }, Vec2{ 0,-1 });
			Shot = true;
		}
	}

	/*if (keyData.scanCode['W']) {
		m_pos.y -= speed;
	}
	if (keyData.scanCode['S']) {
		m_pos.y += speed;
	}*/
}

void Player::Collided(Entity& other, World* game)
{
}
