#pragma once
#include "SpawnArea.hpp"
#include "GameObject.h"
#include "Items/Item.h"

enum class ItemType
{
	HealingPotion,
	Ammo,
};

class HealingPotion;
class Ammo;

class ItemGenerator : public GameObject
{
protected:
	ItemGenerator(ItemGenerator&) = delete;
	ItemGenerator& operator=(const ItemGenerator&) = delete;

public:
	ItemGenerator();
	virtual ~ItemGenerator();

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	void SetSize(const sf::Vector2f size);
	void SetSize(float w, float h);
	Item* GenItem(ItemType type);

protected:
	SpawnArea area;
};