#include "stdafx.h"
#include "SceneDev2.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{	
	Scene::Init();
}

void SceneDev2::Enter()
{
	Scene::Enter();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}