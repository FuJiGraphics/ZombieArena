#pragma once
#include "HpBar.h"

class Bullet;
class SceneWave1;
class SceneTemplate;

enum class WeaponType
{
	None,
	Minigun,
	Shotgun,
	Rocket,
	Count,
};

class Player : public GameObject
{
protected:
	Player(Player&) = delete;
	Player& operator=(const Player&) = delete;

public:
	Player(const std::string& texId, const std::string& name = "");
	~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetCamera(Camera& view);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	void SetWeapon(WeaponType type);
	void SetScene(SceneTemplate* scene);
	void SetHP(float hp);
	void SetDelay(float delayTime);
	void SetSpeed(float speed);
	sf::FloatRect GetBoundBox() const;
	void SetBoundBox(float x, float y, float width, float height);
	void SetDebugColor(sf::Color color);
	void SetAttack(float atk);
	void SetAmmo(unsigned int ammo);

	void AddHP(float hp);
	void AddAmmo(unsigned int ammo);
	void OnCollide();
	void OnDamage(int damage);
	unsigned int GetAmmo() const;

	bool IsDie() const { return isDie; }

protected:
	sf::Vector2f prevPos;
	std::string texId;
	sf::Sprite body;
	float atkPower;
	float speed;
	Camera* view;
	HpBar hp;
	unsigned int ammo = 0;

	SceneTemplate* scene = nullptr;
	float delay;
	float delayElap = 0.0f;
	sf::RectangleShape boundBox;
	bool isCollide = false;
	bool isDie = false;
	WeaponType weaponType;
};

