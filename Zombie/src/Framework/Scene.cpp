#include "stdafx.h"
#include "Scene.h"

std::stack<std::string> SceneTemplate::resultData;

Scene::Scene(SceneIds id)
	: id(id)
{
}

void Scene::Init()
{
	ApplyAddGo();
	ApplyRemoveGO();

	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	//for (auto obj : gameObjects)
	//{
	//	obj->Release();
	//	// delete obj;
	//}
	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyAddGo();
	ApplyRemoveGO();
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->Update(dt);
	}
}

void Scene::LateUpdate(float dt)
{
}

void Scene::OnPreDraw()
{
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawQueue;

	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		drawQueue.push(obj);
	}

	while (!drawQueue.empty())
	{
		GameObject* obj = drawQueue.top();
		obj->Draw(window);
		drawQueue.pop();
	}
}

void Scene::OnPostDraw()
{
	ApplyAddGo();
	ApplyRemoveGO();
}

void Scene::RemoveGo(GameObject* obj)
{
	removeGameObjects.push_back(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	list.clear();
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			list.push_back(obj);
		}
	}
	return list.size();
}

void Scene::ApplyAddGo()
{
	for (auto go : addGameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addGameObjects.clear();
}

void Scene::ApplyRemoveGO()
{
	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();
}

sf::Vector2f Scene::ScreenToWorld(const sf::Vector2i& pos) const
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(pos, worldView);
}

sf::Vector2i Scene::WorldToScreen(const sf::Vector2f& pos) const
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(pos, worldView);
}
