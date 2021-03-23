#pragma once
#include "Entity.h"

class BaseEntity : public Entity
{
private:
public:
	BaseEntity(std::string name) : Entity(name) {}
	void Update(Visualisation& vis, World* game) override;
	void Render(Visualisation& vis) override;
	void Collided(Entity& other, World* game) override; 
	void Initialise(Vec2 startPos, Vec2 Direction) override;
	ESide GetSide() const override { return ESide::eNeutral; }
};