#include "stdafx.h"
#include "SceneWave2.h"

SceneWave2::SceneWave2()
	: SceneTemplate(SceneIds::SceneWave2)
{
}

void SceneWave2::Init()
{	
	// Player
	playerData.moveSpeed = 120.f;
	playerData.attackDelay = 0.5f;

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 15.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 1.0f;
	ZombieGenDelayR = 1.0f;
	GenZombieCount = 10;
	CurrZombieCount = GenZombieCount;
	nextScene = SceneIds::SceneWave3;

	// Zen Zombies
	GenListL.push(ZombieType::crawler);
	GenListL.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);
	GenListR.push(ZombieType::crawler);

	SceneTemplate::Init();
}

void SceneWave2::Release()
{
	SceneTemplate::Release();
}

void SceneWave2::Enter()
{
	SceneTemplate::Enter();
}

void SceneWave2::Exit()
{
	SceneTemplate::Exit();
}

void SceneWave2::Update(float dt)
{
	SceneTemplate::Update(dt);
}
