#pragma once
#include "Player.h"
#include "Bullet.h"
#include "HpBar.h"
#include "Wall.h"

class Wall;

enum class ZombieType
{
	crawler,
	chaser,
	bloater,
	Max,
};

class Zombie : public GameObject
{
protected:
	Zombie(Zombie&) = delete;
	Zombie& operator=(const Zombie&) = delete;

public:
	Zombie(const std::string& name = "");
	~Zombie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetCamera(sf::View& view);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	void SetPlayer(Player* player);
	void SetHP(float hp);
	void SetAttack(float atk);
	void SetSpeed(float speed);
	void SetAttackSpeed(float atkSpeed);
	void SetPool(ObjectPool<Zombie>* myPool);
	void SetBoundBox(float x, float y, float width, float height);
	void SetZombieType(ZombieType type);

	sf::FloatRect GetBoundBox() const;
	bool IsCollide(Bullet& bullet);
	bool IsCollide(Wall& wall);
	bool IsCollide(Player& player);
	void OnDamage(int damage);
	bool IsDie() const { return isDie; }

private:
	void ResetBoundBox();

protected:
	sf::Vector2f prevPos;
	ZombieType type;
	sf::Sprite body;
	HpBar hp;

	float atk = 10.f;
	float speed = 50.f;
	float atkSpeed = 1.0f;
	float attackElap = 0.0f;
	bool isDie = false;
	bool isCollidePlayer = false;

	sf::View* view;
	Player* player;
	ObjectPool<Zombie>* myPool = nullptr;
	sf::RectangleShape boundBox;
};

