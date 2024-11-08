#include "stdafx.h"
#include "SceneGameClear.h"

SceneGameClear::SceneGameClear()
	: Scene(SceneIds::SceneGameClear)
{
}

void SceneGameClear::Init()
{
	Scene::Init();
	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
	background.setPosition(0.0f, 0.0f);
	Utils::SetOrigin(background, Origins::MC);
	const auto& size = background.getTexture()->getSize();
	worldView.setCenter({ 0.0f, 0.0f });
	worldView.setSize({ (float)size.x, (float)size.y });

	float tx = (float)size.x * -0.3f;
	float ty = -0.1f;
	// 메뉴 리스트
	const char* items[] = {
		"Congratulations on clearing the game!!"
	};

	// 메뉴 설정
	int menuSize = 1;
	menuItems.resize(menuSize);
	for (int i = 0; i < menuSize; ++i)
	{
		menuItems[i].setFont(FONT_MGR.Get("fonts/zombiecontrol.ttf"));
		menuItems[i].setPosition(tx, (float)size.y * ty);
		menuItems[i].setCharacterSize(60);
		menuItems[i].setString(items[i]);
		ty += 0.1f;
	}

	// 메뉴 충돌 범위
	ty = -0.1f;
	menuBounds.resize(menuSize);
	for (int i = 0; i < menuSize; ++i)
	{
		menuBounds[i].left = tx;
		menuBounds[i].top = (float)size.y * ty;
		menuBounds[i].width = 80.0f * menuItems[i].getString().getSize();
		menuBounds[i].height = 80.0f;
		ty += 0.1f;
	}

	this->ResultDataSave();
}

void SceneGameClear::Release()
{
	Scene::Release();
}

void SceneGameClear::Enter()
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

void SceneGameClear::Exit()
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

void SceneGameClear::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	window.draw(background);
	for (auto& item : menuItems)
	{
		window.draw(item);
	}
}

void SceneGameClear::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		SCENE_MGR.ChangeScene(nextScene, SceneIds::SceneGameClear);
		return;
	}
}

void SceneGameClear::ResultDataSave()
{
	using namespace std;
	std::string currResult;
	currResult = string("Score: ") + std::to_string(SceneTemplate::score) + " (Date: " + Utils::getCurrentDateTime() + ")\n";
	Scene::resultData.push(currResult);
	ofstream out;
	out.open("meta/Result.txt", ios::out);
	if (!out.is_open())
	{
		cerr << "파일 세이브 실패" << endl;
		return;
	}

	while (!Scene::resultData.empty())
	{
		const std::string& data = Scene::resultData.top();
		out << data;
		Scene::resultData.pop();
	}

	out.close();
}

