#pragma once
#include "Scene.h"

class SceneGameClear : public Scene
{
protected:
	SceneGameClear(SceneGameClear&) = delete;
	SceneGameClear& operator=(const SceneGameClear&) = delete;

public:
	SceneGameClear();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;

public:
	void ResultDataSave();

private:
	SceneIds nextScene = SceneIds::SceneGameIntro;
	sf::Sprite background;
	std::vector<sf::Text> menuItems;
	std::vector<sf::FloatRect> menuBounds;
};