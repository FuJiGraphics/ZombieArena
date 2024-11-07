#pragma once

class HpBar : public GameObject
{
protected:
	HpBar(HpBar&) = delete;
	HpBar& operator=(const HpBar&) = delete;

public:
	HpBar();
	virtual ~HpBar();

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
	void SetSize(float width, float height);
	void SetMaxHp(float hp);
	void SetHp(float hp);
	void AddHp(float hp);
	void SetColor(sf::Color color);
	
	float GetHp() const { return (hp <= 0.0f) ? 0.0f : hp; }

	bool operator==(float d);
	bool operator<(float d);
	bool operator>(float d);
	bool operator<=(float d);
	bool operator>=(float d);
	HpBar& operator+=(float d);
	HpBar& operator-=(float d);
	HpBar& operator=(float d);

private:
	void ResetStrideHp();

private:
	float maxHp = 100.f;
	float hp = 100.f;
	sf::RectangleShape bar;
	sf::RectangleShape maxBar;
	sf::Vector2f size;
	sf::Color color;
};