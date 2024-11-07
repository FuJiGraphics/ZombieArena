#pragma once
#include "Scene.h"

class SceneSelect : public Scene
{
protected:
	SceneSelect(SceneSelect&) = delete;
	SceneSelect& operator=(const SceneSelect&) = delete;

public:
	SceneSelect();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;

private:
	SceneIds nextScene = SceneIds::SceneWave1;
	sf::Sprite background;
	std::vector<sf::Text> menuItems;
	std::vector<sf::FloatRect> menuBounds;
};