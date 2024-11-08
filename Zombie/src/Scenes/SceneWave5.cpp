#include "stdafx.h"
#include "SceneWave5.h"

SceneWave5::SceneWave5()
	: SceneTemplate(SceneIds::SceneWave4)
{
	currScene = SceneIds::SceneWave5;
}

void SceneWave5::Init()
{
	currWave = 5;

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 3.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 0.8f;
	ZombieGenDelayR = 0.8f;

	// Gen Zombies
	for (int i = 0; i < 70; ++i)
		GenListL.push(ZombieType::crawler);
	for (int j = 0; j < 70; ++j)
		GenListR.push(ZombieType::crawler);
	for (int i = 0; i < 2; ++i)
		GenListL.push(ZombieType::bloater);
	for (int i = 0; i < 2; ++i)
		GenListR.push(ZombieType::bloater);
	for (int i = 0; i < 50; ++i)
		GenListL.push(ZombieType::chaser);
	for (int j = 0; j < 50; ++j)
		GenListR.push(ZombieType::chaser);



	SceneTemplate::Init();
}

void SceneWave5::Release()
{
	SceneTemplate::Release();
}

void SceneWave5::Enter()
{
	SceneTemplate::Enter();
}

void SceneWave5::Exit()
{
	SceneTemplate::Exit();
}

void SceneWave5::Update(float dt)
{
	SceneTemplate::Update(dt);
}
