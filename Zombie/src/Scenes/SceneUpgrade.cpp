#include "stdafx.h"
#include "SceneUpgrade.h"

SceneUpgrade::SceneUpgrade()
	: Scene(SceneIds::SceneUpgrade)
{
}

void SceneUpgrade::Init()
{
	Scene::Init(); 
	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
	background.setPosition(0.0f, 0.0f);
	Utils::SetOrigin(background, Origins::MC);
	const auto& size = background.getTexture()->getSize();
	worldView.setCenter({ 0.0f, 0.0f });
	worldView.setSize({ (float)size.x, (float)size.y });

	float tx = (float)size.x * -0.2f;
	float ty = -0.3f;
	// 메뉴 리스트
	const char* items[] = {
		"Increased Attack Power",
		"Increased Attack Speed",
		"Increased Run Speed",
		"Increased Max Health",
		"Increased Ammo 5000",
	};

	// 메뉴 설정
	int menuSize = 5;
	menuItems.resize(menuSize);
	for (int i = 0; i < menuSize; ++i)
	{
		menuItems[i].setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
		menuItems[i].setPosition(tx, (float)size.y * ty);
		menuItems[i].setCharacterSize(80);
		menuItems[i].setString(items[i]);
		ty += 0.1f;
	}

	// 메뉴 충돌 범위
	ty = -0.3f;
	menuBounds.resize(menuSize);
	for (int i = 0; i < menuSize; ++i)
	{
		menuBounds[i].left = tx;
		menuBounds[i].top = (float)size.y * ty;
		menuBounds[i].width = 80.0f * menuItems[i].getString().getSize();
		menuBounds[i].height = 80.0f;
		ty += 0.1f;
	}
}

void SceneUpgrade::Release()
{
	Scene::Release();
}

void SceneUpgrade::Enter()
{
	FONT_MGR.Load("fonts/DS-DIGI.ttf");
	FONT_MGR.Load("fonts/zombiecontrol.ttf");
	TEXTURE_MGR.Load("graphics/background.png"); 
	TEXTURE_MGR.Load("Graphics/background_sheet.png");
	TEXTURE_MGR.Load("Graphics/player.png");
	TEXTURE_MGR.Load("Graphics/bloater.png");
	TEXTURE_MGR.Load("Graphics/crawler.png");
	TEXTURE_MGR.Load("Graphics/chaser.png");
	TEXTURE_MGR.Load("Graphics/bullet.png");
	TEXTURE_MGR.Load("Graphics/blood.png");
	TEXTURE_MGR.Load("graphics/health_pickup.png");
	TEXTURE_MGR.Load("graphics/ammo_pickup.png");
	Scene::Enter();
}

void SceneUpgrade::Exit()
{
	FONT_MGR.Unload("fonts/DS-DIGI.ttf");
	FONT_MGR.Unload("fonts/zombiecontrol.ttf");
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("Graphics/background_sheet.png");
	TEXTURE_MGR.Unload("Graphics/player.png");
	TEXTURE_MGR.Unload("Graphics/bloater.png");
	TEXTURE_MGR.Unload("Graphics/crawler.png");
	TEXTURE_MGR.Unload("Graphics/chaser.png");
	TEXTURE_MGR.Unload("Graphics/bullet.png");
	TEXTURE_MGR.Unload("Graphics/blood.png");
	TEXTURE_MGR.Unload("graphics/health_pickup.png");
	TEXTURE_MGR.Unload("graphics/ammo_pickup.png");
	Scene::Exit();
}

void SceneUpgrade::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	window.draw(background);
	for (auto& item : menuItems)
	{
		window.draw(item);
	}
}

void SceneUpgrade::Update(float dt)
{
	Scene::Update(dt);

	auto& window = FRAMEWORK.GetWindow();
	const auto& mousePos = InputMgr::GetMousePosition();
	auto pixelPos = window.mapPixelToCoords(mousePos);
	sf::FloatRect mouseRect = { pixelPos.x - 1.0f, pixelPos.y - 1.0f, 1.0f, 1.0f };
	int click = -1;
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		int size = (int)menuBounds.size();
		for (int i = 0; i < size; ++i)
		{
			if (menuBounds[i].intersects(mouseRect))
			{
				click = i;
				break;
			}
		}
	}

	switch (click)
	{
		case 0:  //"Increased Attack Power",
			SceneTemplate::playerData.atk += 10.f;
			break;
		case 1:	 //"Increased Attack Speed",
			if (SceneTemplate::playerData.weaponType == WeaponType::Minigun)
			{
				float ddx = SceneTemplate::playerData.attackDelay - 0.03f;
				SceneTemplate::playerData.attackDelay = (ddx >= 0.0f) ? ddx : 0.0001f;
			}
			else
			{
				float ddx = SceneTemplate::playerData.attackDelay - 0.4f;
				SceneTemplate::playerData.attackDelay = (ddx >= 0.0f) ? ddx : 0.4f;
			}
			break;
		case 2:	 //"Increased Run Speed",
			SceneTemplate::playerData.moveSpeed += 10.f;
			break;
		case 3:	 //"Increased Max Health",
			SceneTemplate::playerData.hp = 100.f;
			break;
		case 4:	 //"Increased Ammo 5000",
			SceneTemplate::playerData.ammoCount += 5000;
			break;
	}

	if (click >= 0)
	{
		SCENE_MGR.ChangeScene(nextScene, SceneIds::SceneUpgrade);
		return;
	}
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
		nextScene = SceneIds::SceneWave5;
		break;
	case SceneIds::SceneWave5:
		nextScene = SceneIds::SceneWave1;
		break;
	}
}
