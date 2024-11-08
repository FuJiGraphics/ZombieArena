#include "stdafx.h"
#include "SceneMgr.h"

void SceneMgr::Init()
{
	currentSceneRaw = new SceneGameIntro();
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
	if (currentSceneRaw)
		delete currentSceneRaw;
	switch (id)
	{
		case SceneIds::SceneGameInfo:
			currentSceneRaw = new SceneGameInfo();
			break;
		case SceneIds::SceneGameIntro:
			currentSceneRaw = new SceneGameIntro();
			break;
		case SceneIds::SceneSelect:
			currentSceneRaw = new SceneSelect();
			break;
		case SceneIds::SceneGameOver:
			currentSceneRaw = new SceneGameOver();
			break; 
		case SceneIds::SceneGameClear:
			currentSceneRaw = new SceneGameClear();
			break;
		case SceneIds::SceneGameScores:
			currentSceneRaw = new SceneGameScores();
			break;
		case SceneIds::SceneUpgrade: 
			currentSceneRaw = new SceneUpgrade(); 
			((SceneUpgrade*)currentSceneRaw)->SetCurrentScene(currId);
			break;
		case SceneIds::SceneWave1: 
			currentSceneRaw = new SceneWave1(); 
			break;
		case SceneIds::SceneWave2: 
			currentSceneRaw = new SceneWave2(); 
			break;
		case SceneIds::SceneWave3: 
			currentSceneRaw = new SceneWave3(); 
			break;
		case SceneIds::SceneWave4:
			currentSceneRaw = new SceneWave4(); 
			break;
		case SceneIds::SceneWave5:
			currentSceneRaw = new SceneWave5();
			break;
		case SceneIds::ExitGame: 
			isExitGame = true; 
			break;
	}

	if (isExitGame)
		return;

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
}
