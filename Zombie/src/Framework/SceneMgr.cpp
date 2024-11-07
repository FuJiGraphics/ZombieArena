#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "Scenes/SceneUpgrade.h"

void SceneMgr::Init()
{
	currentSceneRaw = new SceneWave1;
	currentSceneRaw->Enter();
	currentSceneRaw->Init();

	currentScene = startScene;
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (currentScene == scene->id)
		{
			scene->Exit();
		}
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id, SceneIds currId)
{
	nextScene = id;

	if (currentSceneRaw)
		delete currentSceneRaw;
	switch (id)
	{
	case SceneIds::SceneUpgrade: 
		currentSceneRaw = new SceneUpgrade(SceneIds::SceneUpgrade); 
		((SceneUpgrade*)currentSceneRaw)->SetCurrentScene(currId);
		break;
		case SceneIds::SceneWave1: currentSceneRaw = new SceneWave1(); break;
		case SceneIds::SceneWave2: currentSceneRaw = new SceneWave2(); break;
		case SceneIds::SceneWave3: currentSceneRaw = new SceneWave3(); break;
		case SceneIds::SceneWave4: currentSceneRaw = new SceneWave4(); break;
	}

	currentSceneRaw->Enter();
	currentSceneRaw->Init();
	InputMgr::Clear();
	currentSceneRaw->Update(currDt);
}

void SceneMgr::Update(float dt)
{
	currDt = dt;
	currentSceneRaw->Update(dt);
}

void SceneMgr::LateUpdate(float dt)
{
	currentSceneRaw->LateUpdate(dt);
}

void SceneMgr::OnPreDraw()
{
	currentSceneRaw->OnPreDraw();
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	currentSceneRaw->OnPreDraw();
	currentSceneRaw->Draw(window);
	currentSceneRaw->OnPostDraw();
}

void SceneMgr::OnPostDraw()
{
	currentSceneRaw->OnPostDraw();

	// scenes[(int)currentScene]->OnPostDraw();
	// if (nextScene != SceneIds::None)
	// {
	// 	scenes[(int)currentScene]->Exit();
	// 	currentScene = nextScene;
	// 	nextScene = SceneIds::None;
	// 	scenes[(int)currentScene]->Enter();
	// }
}
