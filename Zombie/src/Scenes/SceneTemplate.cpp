#include "stdafx.h"
#include "SceneTemplate.h"
#include "Zombie.h"

PlayerData SceneTemplate::playerData;
int SceneTemplate::score = 0;

SceneTemplate::SceneTemplate(SceneIds ids)
	: Scene(ids)
{

}

void SceneTemplate::Init()
{
	isInit = true;
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
	player->SetWeapon(playerData.weaponType);
	player->SetHP(playerData.hp);
	player->SetDelay(playerData.attackDelay);
	player->SetSpeed(playerData.moveSpeed);
	player->SetAmmo(playerData.ammoCount);
	player->SetAttack(playerData.atk);
	player->Init();

	// 타일맵 크기
	const auto& tilemapSize = tilemap->GetLength();
	const auto& tilemapPos = tilemap->GetPosition();
	// 스폰 구역 설정
	spawnLeft.SetPosition(tilemapPos.x - tilemapSize.x * 0.38f, tilemapPos.y);
	spawnLeft.SetSize(tilemapSize.x * 0.15f, tilemapSize.y * 0.90f);
	spawnLeft.SetOrigin(Origins::MC);
	spawnRight.SetPosition(tilemapPos.x + tilemapSize.x * 0.38f, tilemapPos.y);
	spawnRight.SetSize(tilemapSize.x * 0.15f, tilemapSize.y * 0.90f);
	spawnRight.SetOrigin(Origins::MC);

	// 벽 생성
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

	// 아이템 생성 area
	itemGen.SetPosition(tilemapPos);
	itemGen.SetSize(tilemapSize.x * 0.9f, tilemapSize.y * 0.9f);
	itemGen.SetOrigin(Origins::MC);

	// 카메라 설정
	worldView.setSize({ 1920.f, 1080.f });
	worldView.zoom(0.5f);
	worldView.setBlockArea(
		tilemapPos.x - tilemapSize.x * 0.5f,
		tilemapPos.y - tilemapSize.y * 0.5f,
		tilemapPos.x + tilemapSize.x * 0.5f,
		tilemapPos.y + tilemapSize.y * 0.5f);

	// UI 인터페이스 초기화
	uihub.Init();
	uihub.SetTargetCamera(&worldView);
	uihub.SetZombieCount(CurrZombieCount);
	uihub.SetAmmo(player->GetAmmo());
	uihub.SetWave(currWave);

	// 좀비 정보
	GenZombieCount = GenListL.size() + GenListR.size();
}

void SceneTemplate::Release()
{
	if (!isInit)
		return;
	this->DeleteUsedBullets();
	this->DeleteDieZombies();
	gameObjects.remove(tilemap);
	tilemap->Release();
	gameObjects.remove(player);
	delete tilemap;
	delete player;
	SceneTemplate::Exit();
	ApplyRemoveGO();
	CurrZombieCount = 0;
	GenZombieCount = 0;
	while (!GenListL.empty())
		GenListL.pop();
	while (!GenListR.empty())
		GenListR.pop();
	Scene::Release();
}

void SceneTemplate::Enter()
{
	FONT_MGR.Load("fonts/DS-DIGI.ttf");
	FONT_MGR.Load("fonts/zombiecontrol.ttf");
	TEXTURE_MGR.Load("graphics/bloodEffect.png");
	TEXTURE_MGR.Load("Graphics/background_sheet.png");
	TEXTURE_MGR.Load("Graphics/player.png");
	TEXTURE_MGR.Load("Graphics/bloater.png");
	TEXTURE_MGR.Load("Graphics/crawler.png");
	TEXTURE_MGR.Load("Graphics/chaser.png");
	TEXTURE_MGR.Load("Graphics/bullet.png");
	TEXTURE_MGR.Load("Graphics/blood.png");
	TEXTURE_MGR.Load("graphics/health_pickup.png");
	TEXTURE_MGR.Load("graphics/ammo_pickup.png");
}

void SceneTemplate::Exit()
{
	if (!isInit)
		return;

	FONT_MGR.Unload("fonts/DS-DIGI.ttf");
	FONT_MGR.Unload("fonts/zombiecontrol.ttf");
	TEXTURE_MGR.Unload("graphics/bloodEffect.png");
	TEXTURE_MGR.Unload("Graphics/background_sheet.png");
	TEXTURE_MGR.Unload("Graphics/player.png");
	TEXTURE_MGR.Unload("Graphics/bloater.png");
	TEXTURE_MGR.Unload("Graphics/crawler.png");
	TEXTURE_MGR.Unload("Graphics/chaser.png");
	TEXTURE_MGR.Unload("Graphics/bullet.png");
	TEXTURE_MGR.Unload("Graphics/blood.png");
	TEXTURE_MGR.Unload("graphics/health_pickup.png");
	TEXTURE_MGR.Unload("graphics/ammo_pickup.png");
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

	// 비활성화된 오브젝트 정리
	this->DeleteUsedBullets();
	this->DeleteDieZombies();
	this->DeleteEffects();
	this->DeleteItems();

	Scene::Update(dt);

	elapL += dt;
	if (!GenListL.empty() && elapL >= ZombieGenDelayL)
	{
		ZombieType typeL = GenListL.front();
		++CurrZombieCount;
		elapL = 0.0f;
		const auto& newPos = spawnLeft.Spawn();
		Zombie* zombie = AddGo(zombiePool.Take());
		zombie->SetPosition(newPos);
		zombie->SetPlayer(player);
		zombie->SetPool(&zombiePool);
		zombie->SetEffectPool(&effectPool);
		zombie->SetZombieType(typeL);
		GenListL.pop();
	}

	elapR += dt;
	if (!GenListR.empty() && elapR >= ZombieGenDelayR)
	{
		ZombieType typeR = GenListR.front();
		++CurrZombieCount;
		elapR = 0.0f;
		const auto& newPos = spawnRight.Spawn();
		Zombie* zombie = AddGo(zombiePool.Take());
		zombie->SetPosition(newPos);
		zombie->SetPlayer(player);
		zombie->SetPool(&zombiePool);
		zombie->SetEffectPool(&effectPool);
		zombie->SetZombieType(typeR);
		GenListR.pop();
	}

	elapItem += dt;
	if (elapItem >= ItemZenDelay)
	{
		elapItem = 0.0f;
		int ran = Utils::RandomRange(0, 1);
		AddGo(itemGen.GenItem(static_cast<ItemType>(ran)));
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

	// 게임 결과
	// Game Clear
	if (GenListL.empty() && GenListR.empty() && CurrZombieCount <= 0)
	{
		SceneTemplate::Release();
		SCENE_MGR.ChangeScene(SceneIds::SceneUpgrade, currScene);
		return;
	}
	// Game Over
	if (player->IsDie())
	{
		SceneTemplate::Release();
		SCENE_MGR.ChangeScene(SceneIds::SceneGameOver, currScene);
		return;
	}

	// UI 정보 갱신
	uihub.SetAmmo(player->GetAmmo());
	uihub.SetZombieCount(CurrZombieCount);
	uihub.SetScore(score);
	uihub.Update(dt);
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
	
	uihub.Draw(window);
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
		if (!zombie->IsActive() || zombie->IsDie())
			continue;
		zombie->IsCollide(*player);
	}

	std::list<Zombie*> findList;
	for (auto& zombie : zombiePool.used)
		findList.push_back(zombie);
	while (!findList.empty())
	{
		auto find = findList.front();
		findList.pop_front();
		bool findColResult = false;
		for (auto& target : findList)
		{
			if (find->IsCollide(*target))
			{
				findColResult = true;
			}
		}
		if (!findColResult)
			find->SetOverlapZombie(false);
	}

	bool result = false;
	for (auto& wall : walls)
		result = (wall.Intersect(*player)) ? true : result;
	if (result)
		player->SetDebugColor(sf::Color::Red);
	else
		player->SetDebugColor(sf::Color::Green);
	for (auto& wall : walls)
	{
		for (auto& zombie : zombiePool)
		{
			if (!zombie->IsActive() || zombie->IsDie())
				continue;

			result = (wall.Intersect(*zombie)) ? true : result;
		}
	}
	if (result)
		player->SetDebugColor(sf::Color::Red);
	else
		player->SetDebugColor(sf::Color::Green);

	// 아이템 충돌 처리
	for (auto& item : EnableCollideItemList)
	{
		if (player->IsActive() && !player->IsDie())
		{
			if (item->IsActive() && item->EnabledCollide())
			{
				if (item->GetBoundBox().intersects(player->GetBoundBox()))
				{
					ItemType type = item->GetType();
					switch (type)
					{
					case ItemType::Ammo:
						((Ammo*)item)->OnCollide(*player);
						break;
					case ItemType::HealingPotion:
						((HealingPotion*)item)->OnCollide(*player);
						break;
					}
					break;
				}
			}
		}
	}
}

void SceneTemplate::DeleteUsedBullets()
{
	for (auto& bullet : bulletPool.used)
	{
		if (bullet->IsDie())
		{
			delBulletList.push_back(bullet);
		}
	}
	while (!delBulletList.empty())
	{
		Bullet* del = delBulletList.front();
		delBulletList.pop_front();
		bulletPool.used.remove(del);
		gameObjects.remove(del);
		delete del;
		del = nullptr;
	}
}

void SceneTemplate::DeleteDieZombies()
{
	for (auto& zombie : zombiePool.unused)
	{
		if (zombie->IsDie())
		{
			delZombieList.push_back(zombie);
		}
	}
	while (!delZombieList.empty())
	{
		Zombie* del = delZombieList.front();
		delZombieList.pop_front();
		zombiePool.unused.remove(del);
		gameObjects.remove(del);
		delete del;
		del = nullptr;
	}
}

void SceneTemplate::DeleteEffects()
{
	for (auto& effect : effectPool.unused)
	{
		if (!effect->IsActive())
		{
			delEffectList.push_back(effect);
		}
	}
	while (!delEffectList.empty())
	{
		Effect* del = delEffectList.front();
		delEffectList.pop_front();
		effectPool.unused.remove(del);
		gameObjects.remove(del);
		delete del;
		del = nullptr;
	}
}

void SceneTemplate::DeleteItems()
{
	for (auto& item : itemPool.unused)
	{
		if (!item->IsActive())
		{
			delItemList.push_back(item);
		}
	}
	while (!delItemList.empty())
	{
		Item* del = delItemList.front();
		delItemList.pop_front();
		itemPool.unused.remove(del);
		gameObjects.remove(del);
		delete del;
		del = nullptr;
	}
}
