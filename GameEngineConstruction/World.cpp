#include "World.h"
#include"Entity.h"
#include"Visualisation.h"
#include"Enemy.h"
#include "Player.h"
#include "BaseEntity.h"
#include "Bullet.h"
#include "Vec2.h"
#include <HAPI_lib.h>

HAPI_TColour BGColour(HAPI_TColour::BLACK);
using namespace HAPISPACE;
constexpr int NumBullets = 10;
constexpr int NumEnemys = 5;

bool World::LoadLevel()
{
	m_vis->LoadSprite("Data\\Background.png", "Background");
	BaseEntity* NewEntity = new BaseEntity("Background");
	NewEntity->setStart(0, 0, 752, 800);
	m_Entities.push_back(NewEntity);

	m_vis->LoadSprite("Data\\laser.png", "Bullet");
	m_BulletStart = m_Entities.size();
	for (int i = 0; i < NumBullets; i++)
	{
		Bullet* newBullet = new Bullet("Bullet");
		newBullet->setStart(10, 10, 10, 10);
		m_Entities.push_back(newBullet);
	}

	m_vis->LoadSprite("Data\\enemy-small.png", "Enemy");
	m_EnemyStart = m_Entities.size();
	for (int i = 0; i < NumEnemys; i++)
	{
		Enemy* newEnemy = new Enemy("Enemy");
		newEnemy->setStart(rand() % (m_screenw - 58) + 1, rand() % (m_screenh/2 - 58) + 1, 58, 58);
		m_Entities.push_back(newEnemy);
	};
	
	m_vis->LoadSprite("Data\\ship.png", "Player1");
	Player* NewEntity1 = new Player("Player1");
	NewEntity1->setStart(376,700, 64, 64);
	m_Entities.push_back(NewEntity1);

	return true;
};

void World::Update()
{
	//render entities
	for (auto entity : m_Entities)
	{
		entity->Render(*m_vis);
	};

	for (auto entity : m_Entities)
	{
		entity->Update(*m_vis, this);
	};
	//check collisions 
	for (size_t entity1 = 0; entity1 < m_Entities.size();entity1++)
	{
		if (m_Entities[entity1]->GetSide() != ESide::eNeutral)
		{
			for (size_t entity2 = entity1 + 1; entity2 < m_Entities.size(); entity2++)
			{
				if (m_Entities[entity1]->CheckCollision(*m_Entities[entity2]))
				{
					m_Entities[entity1]->Collided(*m_Entities[entity2], this);
				}
			}
		}
	}
	//m_vis->DrawStars();
	//m_vis->ClearToColour(BGColour);

};

bool World::Initialise(int width, int height)
{
	m_screenw = width;
	m_screenh = height;
	m_vis = new Visualisation;
	m_vis->Initialise(width, height);
	return true;
}

void World::FireBullet(Vec2 StartPos, Vec2 direction)
{

	for (int i = m_BulletStart; i <m_BulletStart + NumBullets; i++)
	{
		if (!m_Entities[i]->isAlive())
		{
			m_Entities[i]->Initialise(StartPos, direction);
			return;
		};
	}
}

void World::NewEnemy(Vec2 StartPos, float dx, float dy)
{
	for (int i = m_EnemyStart; i < m_EnemyStart + NumEnemys; i++)
	{
		if (!m_Entities[i]->isAlive() )
		{
			m_Entities[i]->Initialise(StartPos, Vec2{ dx,1 });
		}
	}
};
