#include "stdafx.h"
#include "SceneWave4.h"

SceneWave4::SceneWave4()
	: SceneTemplate(SceneIds::SceneWave4)
{
	currScene = SceneIds::SceneWave4;
}

void SceneWave4::Init()
{
	currWave = 4;

	// Player
	playerData.attackDelay = 0.01f;

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 0.5f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 0.2f;
	ZombieGenDelayR = 0.2f;

	// Zen Zombies
	for (int i = 0; i < 100; ++i)
		GenListL.push(ZombieType::crawler);
	for (int i = 0; i < 100; ++i)
		GenListR.push(ZombieType::crawler);
	for (int i = 0; i < 100; ++i)
		GenListL.push(ZombieType::chaser);
	for (int i = 0; i < 100; ++i)
		GenListR.push(ZombieType::chaser);

	SceneTemplate::Init();
}

void SceneWave4::Release()
{
	SceneTemplate::Release();
}

void SceneWave4::Enter()
{
	SceneTemplate::Enter();
}

void SceneWave4::Exit()
{
	SceneTemplate::Exit();
}

void SceneWave4::Update(float dt)
{
	SceneTemplate::Update(dt);
}
