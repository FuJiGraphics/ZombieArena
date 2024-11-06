#pragma once
#include "GameObject.h"

class Item : public GameObject
{
protected:
	Item(Item&) = delete;
	Item& operator=(const Item&) = delete;

public:
	Item(const std::string& name = "");
	virtual ~Item() = default;

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
	void SetTextureId(const std::string& texId);

private:
	std::string texId;
	sf::Sprite body;
	sf::RectangleShape boundBox;
};

