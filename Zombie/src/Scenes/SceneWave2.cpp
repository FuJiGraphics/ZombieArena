#include "stdafx.h"
#include "SceneWave2.h"

SceneWave2::SceneWave2()
	: SceneTemplate(SceneIds::SceneWave2)
{
	currScene = SceneIds::SceneWave2;
}

void SceneWave2::Init()
{
	currWave = 2;

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 5.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 0.95f;
	ZombieGenDelayR = 0.95f;

	// Gen Zombies
	for (int i = 0; i < 25; ++i)
		GenListL.push(ZombieType::crawler);
	for (int j = 0; j < 25; ++j)
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
