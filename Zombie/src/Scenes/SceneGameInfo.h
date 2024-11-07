#pragma once
#include "Scene.h"

class SceneGameInfo : public Scene
{
protected:
	SceneGameInfo(SceneGameInfo&) = delete;
	SceneGameInfo& operator=(const SceneGameInfo&) = delete;

public:
	SceneGameInfo();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;

private:
	SceneIds nextScene = SceneIds::SceneGameIntro;
	sf::Sprite background;
	std::vector<sf::Text> menuItems;
	std::vector<sf::FloatRect> menuBounds;
};