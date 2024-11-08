#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"
#include "Zombie.h"
#include "SpawnArea.hpp"
#include "Wall.h"
#include "ItemGenerator.h"
#include "UIHub.h"
#include "Effect.h"
#include "Items/Item.h"

class Zombie;

struct PlayerData
{
	float atk = 10.0f;
	float hp = 100.0f;
	float moveSpeed = 100.0f;
	float attackDelay = 1.0f;
	unsigned int ammoCount = 500;
	WeaponType weaponType;

	void SetWeapon(WeaponType weapon = WeaponType::None)
	{
		hp = 100.f;
		if (weapon != WeaponType::None && weapon != WeaponType::Count)
			weaponType = weapon;
		switch (weaponType)
		{
			case WeaponType::Minigun:
				moveSpeed = 100.f;
				atk = 5.f;
				attackDelay = 0.1f;
				ammoCount = 500;
				break;
			case WeaponType::Shotgun:
				moveSpeed = 90.f;
				atk = 7.f;
				attackDelay = 2.0f;
				ammoCount = 1000;
				break;
			case WeaponType::Rocket:
				moveSpeed = 90.f;
				atk = 50.f;
				attackDelay = 1.5f;
				ammoCount = 8;
				break;
		}
	}
};

class SceneTemplate : public Scene
{
protected:
	SceneTemplate(SceneTemplate&) = delete;
	SceneTemplate& operator=(const SceneTemplate&) = delete;

public:
	SceneTemplate(SceneIds ids);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombies(int count);
	void OnCollide();

	bool IsOnDebugBox() const { return enabledDebugBox; }
	bool IsOnDebugWall() const { return enabledDebugWall; }
	bool IsOnDebugArea() const { return enabledDebugArea; }

	void DeleteUsedBullets();
	void DeleteDieZombies();
	void DeleteEffects();
	void DeleteItems();

public:
	ObjectPool<Effect>	effectPool;
	ObjectPool<Zombie>	zombiePool;
	ObjectPool<Bullet>	bulletPool;
	ObjectPool<Item>	itemPool;
	std::list<Bullet*>	delBulletList;
	std::list<Zombie*>	delZombieList;
	std::list<Effect*>	delEffectList;
	std::list<Item*>	delItemList;

	// 충돌 리스트
	std::list<Item*>	EnableCollideItemList;

	// Item
	float elapItem = 0.0f;
	float ItemZenDelay = 15.0f;

	// Zombies
	float elapR = 0.0f;
	float elapL = 0.0f;
	float ZombieGenDelayL = 1.0f;
	float ZombieGenDelayR = 1.0f;
	int GenZombieCount = 0;
	int CurrZombieCount = 0;
	SceneIds currScene;
	SceneIds LastWave;
	std::queue<ZombieType> GenListL;
	std::queue<ZombieType> GenListR;

	int currWave = 0;
	static PlayerData playerData;
	static int score;
	TileMap* tilemap;

	SpawnArea spawnLeft;
	SpawnArea spawnRight;

private:
	Player* player;
	Wall walls[4];
	ItemGenerator itemGen;
	UIHub uihub;

	bool enabledDebugBox = false;
	bool enabledDebugWall = false;
	bool enabledDebugArea = false;

	bool isInit = false;
};