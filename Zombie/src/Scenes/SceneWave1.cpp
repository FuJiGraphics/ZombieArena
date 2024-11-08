#include "stdafx.h"
#include "SceneWave1.h"

SceneWave1::SceneWave1()
	: SceneTemplate(SceneIds::SceneWave1)
{
	currScene = SceneIds::SceneWave1;
}

void SceneWave1::Init()
{
	currWave = 1;
	LastWave = SceneIds::SceneWave5;

	// Player Start Stat
	playerData.SetWeapon();

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 5.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 1.0f;
	ZombieGenDelayR = 1.0f;

	// Gen Zombies
	for (int i = 0; i < 10; ++i)
		GenListL.push(ZombieType::crawler);
	for (int j = 0; j < 10; ++j)
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
