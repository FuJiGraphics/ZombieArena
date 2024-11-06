#include "stdafx.h"
#include "SceneWave1.h"

SceneWave1::SceneWave1()
	: SceneTemplate(SceneIds::SceneWave1)
{
}

void SceneWave1::Init()
{
	// Player
	playerData.hp = 100.f;
	playerData.moveSpeed = 120.f;
	playerData.attackDelay = 0.8f;

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 15.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 1.0f;
	ZombieGenDelayR = 1.0f;
	GenZombieCount = 4;
	CurrZombieCount = GenZombieCount;
	nextScene = SceneIds::SceneWave2;

	// Zen Zombies
	GenListL.push(ZombieType::crawler);
	GenListL.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);

	SceneTemplate::Init();
}

void SceneWave1::Release()
{
	SceneTemplate::Release();
}

void SceneWave1::Enter()
{
	SceneTemplate::Enter();
}

void SceneWave1::Exit()
{
	SceneTemplate::Exit();
}

void SceneWave1::Update(float dt)
{
	SceneTemplate::Update(dt);
}
