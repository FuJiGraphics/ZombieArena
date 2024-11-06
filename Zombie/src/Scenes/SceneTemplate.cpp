#include "stdafx.h"
#include "SceneTemplate.h"
#include "Zombie.h"

PlayerData SceneTemplate::playerData;

SceneTemplate::SceneTemplate(SceneIds ids)
	: Scene(ids)
{

}

void SceneTemplate::Init()
{
	isInit = true;
	FONT_MGR.Load("fonts/DS-DIGI.ttf");
	Scene::Init();

	tilemap = AddGo(new TileMap("graphics/background_sheet.png"));
	tilemap->Init();
	tilemap->SetSize(30, 30);
	for (int i = 0; i < 30; ++i)
	{
		tilemap->Push({ 50.f, 50.f }, { 0.0f, 150.0f, 50.0f, 50.0f });
	}
	for (int i = 0; i < 28; ++i)
	{
		tilemap->Push({ 50.f, 50.f }, { 0.0f, 150.0f, 50.0f, 50.0f });
		for (int j = 0; j < 28; ++j)
		{
			float texTile = Utils::RandomRange(0, 2) * 50.f;
			tilemap->Push({ 50.f, 50.f }, { 0.0f, texTile, 50.0f, 50.0f });
		}
		tilemap->Push({ 50.f, 50.f }, { 0.0f, 150.0f, 50.0f, 50.0f });
	}
	for (int i = 0; i < 30; ++i)
	{
		tilemap->Push({ 50.f, 50.f }, { 0.0f, 150.0f, 50.0f, 50.0f });
	}
	tilemap->SetPosition({ 0.0f, 0.0f });
	tilemap->SetOrigin(Origins::MC);
	player = AddGo(new Player("graphics/player.png"));
	player->SetPosition({ 0.0f, 0.0f });
	player->SetCamera(worldView);
	player->SetScene(this);
	player->SetHP(playerData.hp);
	player->SetDelay(playerData.attackDelay);
	player->SetSpeed(playerData.moveSpeed);
	player->Init();

	// Ÿ�ϸ� ũ��
	const auto& tilemapSize = tilemap->GetLength();
	const auto& tilemapPos = tilemap->GetPosition();
	// ���� ���� ����
	spawnLeft.SetPosition(tilemapPos.x - tilemapSize.x * 0.38f, tilemapPos.y);
	spawnLeft.SetSize(tilemapSize.x * 0.15f, tilemapSize.y * 0.90f);
	spawnLeft.SetOrigin(Origins::MC);
	spawnRight.SetPosition(tilemapPos.x + tilemapSize.x * 0.38f, tilemapPos.y);
	spawnRight.SetSize(tilemapSize.x * 0.15f, tilemapSize.y * 0.90f);
	spawnRight.SetOrigin(Origins::MC);

	// �� ����
	walls[0].SetPosition({ tilemapPos.x - tilemapSize.x * 0.5f, tilemapPos.y - tilemapSize.y * 0.5f });
	walls[0].SetSize(50.f, tilemapSize.y);
	walls[0].Init();
	walls[1].SetPosition({ tilemapPos.x + tilemapSize.x * 0.467f, tilemapPos.y - tilemapSize.y * 0.5f });
	walls[1].SetSize(50.f, tilemapSize.y);
	walls[1].Init();
	walls[2].SetPosition({ tilemapPos.x - tilemapSize.x * 0.5f, tilemapPos.y - tilemapSize.y * 0.5f });
	walls[2].SetSize(tilemapSize.x, 50.f);
	walls[2].Init();
	walls[3].SetPosition({ tilemapPos.x - tilemapSize.x * 0.5f , tilemapPos.y + tilemapSize.y * 0.467f });
	walls[3].SetSize(tilemapSize.x, 50.f);
	walls[3].Init();

	// ������ ���� area
	itemGen.SetPosition(tilemapPos);
	itemGen.SetSize(tilemapSize.x * 0.9f, tilemapSize.y * 0.9f);
	itemGen.SetOrigin(Origins::MC);

	// ī�޶� ����
	worldView.setSize({ 1920.f, 1080.f });
	worldView.zoom(0.5f);
	worldView.setBlockArea(
		tilemapPos.x - tilemapSize.x * 0.5f,
		tilemapPos.y - tilemapSize.y * 0.5f,
		tilemapPos.x + tilemapSize.x * 0.5f,
		tilemapPos.y + tilemapSize.y * 0.5f);
}

void SceneTemplate::Release()
{
	if (!isInit)
		return;

	RemoveGo(tilemap);
	tilemap->Release();
	RemoveGo(player);
	delete tilemap;
	delete player;
	SceneTemplate::Exit();
	ApplyRemoveGO();
	Scene::Release();
}

void SceneTemplate::Enter()
{
	FONT_MGR.Load("fonts/DS-DIGI.ttf");
	TEXTURE_MGR.Load("Graphics/background_sheet.png");
	TEXTURE_MGR.Load("Graphics/player.png");
	TEXTURE_MGR.Load("Graphics/bloater.png");
	TEXTURE_MGR.Load("Graphics/crawler.png");
	TEXTURE_MGR.Load("Graphics/chaser.png");
	TEXTURE_MGR.Load("Graphics/bullet.png");
}

void SceneTemplate::Exit()
{
	if (!isInit)
		return;

	FONT_MGR.Unload("fonts/DS-DIGI.ttf");
	TEXTURE_MGR.Unload("Graphics/background_sheet.png");
	TEXTURE_MGR.Unload("Graphics/player.png");
	TEXTURE_MGR.Unload("Graphics/bloater.png");
	TEXTURE_MGR.Unload("Graphics/crawler.png");
	TEXTURE_MGR.Unload("Graphics/chaser.png");
	TEXTURE_MGR.Unload("Graphics/bullet.png");
	for (auto zombie : zombies)
	{
		RemoveGo(zombie);
		zombiePool.Return(zombie);
	}
	zombies.clear();
	for (auto zombie : zombiePool.unused)
		RemoveGo(zombie);
	for (auto zombie : zombiePool.used)
		RemoveGo(zombie);
	for (auto bullet : bulletPool.unused)
		RemoveGo(bullet);
	for (auto bullet : bulletPool.used)
		RemoveGo(bullet);
	Scene::Exit();
}

void SceneTemplate::Update(float dt)
{
	if (!isInit)
		return;

	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Num9))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneWave1);
		return;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num0))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneWave2);
		return;
	}

	elapL += dt;
	if (!GenListL.empty() && elapL >= ZombieGenDelayL && GenZombieCount)
	{
		ZombieType typeL = GenListL.front();
		GenZombieCount -= 1;
		elapL = 0.0f;
		const auto& newPos = spawnLeft.Spawn();
		Zombie* zombie = AddGo(zombiePool.Take());
		zombie->SetPosition(newPos);
		zombie->SetPlayer(player);
		zombie->SetPool(&zombiePool);
		zombie->SetZombieType(typeL);
		GenListL.pop();
	}

	elapR += dt;
	if (!GenListR.empty() && elapR >= ZombieGenDelayR && GenZombieCount)
	{
		ZombieType typeR = GenListR.front();
		GenZombieCount -= 1;
		elapR = 0.0f;
		const auto& newPos = spawnRight.Spawn();
		Zombie* zombie = AddGo(zombiePool.Take());
		zombie->SetPosition(newPos);
		zombie->SetPlayer(player);
		zombie->SetPool(&zombiePool);
		zombie->SetZombieType(typeR);
		GenListR.pop();
	}

	elapItem += dt;
	if (elapItem >= ItemZenDelay)
	{
		elapItem = 0.0f;
		AddGo(itemGen.GenItem());
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		enabledDebugBox = (enabledDebugBox) ? false : true;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		enabledDebugArea = (enabledDebugArea) ? false : true;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		enabledDebugWall = (enabledDebugWall) ? false : true;
	}
	this->OnCollide();

	if (player->IsDie())
	{
		FRAMEWORK.SetTimeScale(0.0f);
		SCENE_MGR.ChangeScene(SceneIds::SceneWave1);
		return;
	}

	if (CurrZombieCount <= 0)
	{
		SceneTemplate::Release();
		SCENE_MGR.ChangeScene(nextScene);
		return;
	}
}

void SceneTemplate::Draw(sf::RenderWindow& window)
{
	if (!isInit)
		return;

	window.setView(worldView);
	Scene::Draw(window);
	if (enabledDebugArea)
	{
		spawnLeft.Draw(window);
		spawnRight.Draw(window);
		itemGen.Draw(window);
	}
	for (auto& wall : walls)
	{
		wall.Draw(window);
	}
}

void SceneTemplate::SpawnZombies(int count)
{
	if (!isInit)
		return;

	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = zombiePool.Take();
		AddGo(zombie);
		zombie->SetPlayer(player);
		const auto& newPos = tilemap->GetPosition();
	}
}

void SceneTemplate::OnCollide()
{
	if (!isInit)
		return;

	bool isCollide = false;
	for (auto& bullet : bulletPool)
	{
		if (!bullet->IsActive() || bullet->IsDie())
			continue;

		for (auto& zombie : zombiePool)
		{
			if (!zombie->IsActive() || zombie->IsDie())
				continue;

			if (zombie->IsCollide(*bullet))
			{
				bullet->OnCollide(zombie);
				isCollide = true;
				break;
			}
		}
		if (isCollide)
			break;
	}

	for (auto& zombie : zombiePool)
	{
		zombie->IsCollide(*player);
	}

	bool result = false;
	for (auto& wall : walls)
		result = (wall.Intersect(*player)) ? true : result;
	if (result)
		player->SetDebugColor(sf::Color::Red);
	else
		player->SetDebugColor(sf::Color::Green);
}
