#include "stdafx.h"
#include "SceneWave3.h"

SceneWave3::SceneWave3()
	: SceneTemplate(SceneIds::SceneWave3)
{
	currScene = SceneIds::SceneWave3;
}

void SceneWave3::Init()
{
	currWave = 3;

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 4.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 1.0f;
	ZombieGenDelayR = 1.0f;

	// Gen Zombies
	for (int i = 0; i < 20; ++i)
		GenListL.push(ZombieType::crawler);
	for (int j = 0; j < 20; ++j)
		GenListR.push(ZombieType::crawler);
	for (int i = 0; i < 10; ++i)
		GenListL.push(ZombieType::chaser);
	for (int j = 0; j < 10; ++j)
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
