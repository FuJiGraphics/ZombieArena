#pragma once
#include "Scene.h"

class SceneGameOver : public Scene
{
protected:
	SceneGameOver(SceneGameOver&) = delete;
	SceneGameOver& operator=(const SceneGameOver&) = delete;

public:
	SceneGameOver();

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