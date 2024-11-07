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

	// Item
	elapItem = 0.0f;
	ItemZenDelay = 3.0f;

	// Zombies
	elapR = 0.0f;
	elapL = 0.0f;
	ZombieGenDelayL = 0.8f;
	ZombieGenDelayR = 0.8f;

	// Gen Zombies
	for (int i = 0; i < 40; ++i)
		GenListL.push(ZombieType::crawler);
	for (int j = 0; j < 40; ++j)
		GenListR.push(ZombieType::crawler);
	for (int i = 0; i < 30; ++i)
		GenListL.push(ZombieType::chaser);
	for (int j = 0; j < 30; ++j)
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
