#pragma once
#include "HpBar.h"

class Bullet;
class SceneWave1;
class SceneTemplate;

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
	void SetScene(SceneTemplate* scene);
	void SetHP(float hp);
	void SetDelay(float delayTime);
	void SetSpeed(float speed);
	sf::FloatRect GetBoundBox() const;
	void SetBoundBox(float x, float y, float width, float height);
	void SetDebugColor(sf::Color color);

	void OnCollide();
	void OnDamage(int damage);

	bool IsDie() const { return isDie; }

protected:
	sf::Vector2f prevPos;
	std::string texId;
	sf::Sprite body;
	float speed;
	Camera* view;
	HpBar hp;

	SceneTemplate* scene = nullptr;
	float delay;
	float delayElap = 0.0f;
	sf::RectangleShape boundBox;
	bool isCollide = false;
	bool isDie = false;
};

