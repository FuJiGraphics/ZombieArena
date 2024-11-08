#pragma once
#include "Scene.h"

class SceneGameScores : public Scene
{
protected:
	SceneGameScores(SceneGameScores&) = delete;
	SceneGameScores& operator=(const SceneGameScores&) = delete;

public:
	SceneGameScores();

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