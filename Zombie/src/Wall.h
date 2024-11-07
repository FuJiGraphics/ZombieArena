#pragma once

#include "Framework/GameObject.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

class Wall : public GameObject
{
protected:
	Wall(Wall&) = delete;
	Wall& operator=(const Wall&) = delete;

public:
	Wall(const std::string& name = "");
	virtual ~Wall() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void Init() override;
	void Release() override;
	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool Intersect(Player& obj);
	bool Intersect(Zombie& obj);
	bool Intersect(Bullet& obj);

public:
	void SetSize(float width, float height);

private:
	sf::RectangleShape	body;
	sf::Vector2f		size;
};