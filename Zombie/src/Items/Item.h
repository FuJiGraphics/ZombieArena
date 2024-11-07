#pragma once
#include "GameObject.h"

enum class ItemType
{
	HealingPotion,
	Ammo,
};


class Item : public GameObject
{
protected:
	Item(Item&) = delete;
	Item& operator=(const Item&) = delete;

public:
	Item(ItemType type);
	virtual ~Item() = default;

	void SetSortingLayer(SortingLayers layer, int order);
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	void SetDuration(float duration);
	void SetTexture(const std::string& path);
	void SetObjectPool(ObjectPool<Item>& myPool);
	void SetBoundBox(float w = 0.0f, float h = 0.0f);
	void SetEnableCollide(bool enabled);

	bool EnabledCollide() const;
	sf::FloatRect GetBoundBox() const;
	ItemType GetType() const;

	// 상호작용 설정
	virtual void OnCollide(Player& player);
	virtual void OnCollide(Zombie& player);

private:
	sf::Sprite body;
	float duration = 0.0f;
	float elap = 0.0f;
	ObjectPool<Item>* myPool = nullptr;
	sf::RectangleShape boundBox;
	bool isCollide = false;
	bool enabledCollide = false;
	ItemType type;
};

