#pragma once
#include "GameObject.h"

class Zombie;

class Bullet : public GameObject
{
protected:
	Bullet(Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;

public:
	Bullet(const std::string& name = "");
	~Bullet() = default;

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
	void SetDirection(const sf::Vector2f& dir);
	void SetSpeed(float speed);
	void SetAttack(float atk);
	void SetPool(ObjectPool<Bullet>* myPool);
	void SetBoundBox(float x, float y, float width, float height);
	void SetKnockbackDuration(float duration);
	void SetWeaponType(WeaponType type);

	sf::FloatRect GetBoundBox() const;
	void OnCollide(Zombie* zombie);
	void OnCollide();
	bool IsDie() const { return isDie; }

private:
	sf::Sprite body;
	sf::Vector2f dir;
	float speed;
	float duration = 7.f;
	float elap = 0.0f;
	float atk = 5.f;
	float KnockbackDuration = 0.0f;
	bool isDie = false;
	ObjectPool<Bullet>* myPool = nullptr;

	WeaponType weaponType;
	sf::RectangleShape boundBox;
};
