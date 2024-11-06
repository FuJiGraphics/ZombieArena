#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"
#include "Zombie.h"
#include "SpawnArea.hpp"
#include "Wall.h"
#include "ItemGenerator.h"

class Zombie;

struct PlayerData
{
	float hp;
	float moveSpeed;
	float attackDelay;
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

public:
	ObjectPool<Zombie> zombiePool;
	ObjectPool<Bullet> bulletPool;

	// Item
	float elapItem = 0.0f;
	float ItemZenDelay = 15.0f;

	// Zombies
	float elapR = 0.0f;
	float elapL = 0.0f;
	float ZombieGenDelayL = 1.0f;
	float ZombieGenDelayR = 1.0f;
	int GenZombieCount = 10;
	int CurrZombieCount = 10;
	SceneIds nextScene;
	std::queue<ZombieType> GenListL;
	std::queue<ZombieType> GenListR;

	static PlayerData playerData;

private:
	TileMap* tilemap;
	Player* player;
	std::list<Zombie*> zombies;
	SpawnArea spawnLeft;
	SpawnArea spawnRight;
	Wall walls[4];
	ItemGenerator itemGen;

	bool enabledDebugBox = true;
	bool enabledDebugWall = true;
	bool enabledDebugArea = true;

	bool isInit = false;
};