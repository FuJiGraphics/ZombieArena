#include "stdafx.h"
#include "SceneUpgrade.h"

SceneUpgrade::SceneUpgrade(SceneIds ids)
	: Scene(ids)
{
}

void SceneUpgrade::Init()
{
	Scene::Init();
}

void SceneUpgrade::Release()
{
	Scene::Release();
}

void SceneUpgrade::Enter()
{
	Scene::Enter();
}

void SceneUpgrade::Exit()
{
	Scene::Exit();
}

void SceneUpgrade::Draw(sf::RenderWindow& window)
{

}

void SceneUpgrade::Update(float dt)
{
	Scene::Update(dt);
}

void SceneUpgrade::SetCurrentScene(SceneIds id)
{
	switch (id)
	{
	case SceneIds::SceneWave1: 
		nextScene = SceneIds::SceneWave2;
		break;
	case SceneIds::SceneWave2:
		nextScene = SceneIds::SceneWave3;
		break;
	case SceneIds::SceneWave3:
		nextScene = SceneIds::SceneWave4;
		break;
	case SceneIds::SceneWave4:
		nextScene = SceneIds::SceneWave1;
		break;
	}
}
