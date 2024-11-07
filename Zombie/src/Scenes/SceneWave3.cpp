#include "stdafx.h"
#include "SceneWave3.h"

SceneWave3::SceneWave3()
	: SceneTemplate(SceneIds::SceneWave3)
{
}

void SceneWave3::Init()
{
	currWave = 3;

	// Player
	playerData.attackDelay = 0.01f;

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 15.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 1.0f;
	ZombieGenDelayR = 1.0f;
	nextScene = SceneIds::SceneWave4;

	// Zen Zombies
	for (int i = 0; i < 7; ++i)
		GenListL.push(ZombieType::crawler);
	for (int i = 0; i < 7; ++i)
		GenListR.push(ZombieType::crawler);
	for (int i = 0; i < 3; ++i)
		GenListL.push(ZombieType::chaser);
	for (int i = 0; i < 3; ++i)
		GenListR.push(ZombieType::chaser);

	SceneTemplate::Init();
}

void SceneWave3::Release()
{
	SceneTemplate::Release();
}

void SceneWave3::Enter()
{
	SceneTemplate::Enter();
}

void SceneWave3::Exit()
{
	SceneTemplate::Exit();
}

void SceneWave3::Update(float dt)
{
	SceneTemplate::Update(dt);
}
