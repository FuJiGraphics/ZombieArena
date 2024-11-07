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
	float hp = 100.0f;
	float moveSpeed = 100.0f;
	float attackDelay = 1.0f;
	unsigned int ammoCount = 500;
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
	std::queue<ZombieType> GenListL;
	std::queue<ZombieType> GenListR;

	int currWave = 0;
	static PlayerData playerData;
	static int score;

private:
	TileMap* tilemap;
	Player* player;
	SpawnArea spawnLeft;
	SpawnArea spawnRight;
	Wall walls[4];
	ItemGenerator itemGen;
	UIHub uihub;

	bool enabledDebugBox = false;
	bool enabledDebugWall = false;
	bool enabledDebugArea = false;

	bool isInit = false;
};