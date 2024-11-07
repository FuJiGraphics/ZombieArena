#pragma once
#include "GameObject.h"

class UIHub : public GameObject
{
public:
	UIHub() = default;
	virtual ~UIHub() = default;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	void SetAmmo(int ammo);
	void SetScore(int score);
	void SetZombieCount(int count);
	void SetWave(int wave);
	void SetTargetCamera(Camera* target);

private:
	TextUI<int> ammo;
	TextUI<int> score;
	TextUI<int> zombieCount;
	TextUI<int> waveCount;
	Camera* camera = nullptr;
};