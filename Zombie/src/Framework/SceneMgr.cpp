#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"

void SceneMgr::Init()
{
	// scenes.push_back(new SceneDev1());	
	// scenes.push_back(new SceneDev2());
	// scenes.push_back(new SceneWave1());
	// scenes.push_back(new SceneWave2());
	// scenes.push_back(new SceneWave2());
	// scenes.push_back(new SceneWave3());
	// scenes.push_back(new SceneWave4());
	// scenes.push_back(new SceneWave5());
	currentSceneRaw = new SceneWave4;
	currentSceneRaw->Enter();
	currentSceneRaw->Init();

	currentScene = startScene;
	// scenes[(int)currentScene]->Enter();
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

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;

	if (currentSceneRaw)
		delete currentSceneRaw;
	switch (id)
	{
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
