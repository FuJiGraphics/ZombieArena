#pragma once
#include "Scene.h"

class SceneGameIntro : public Scene
{
protected:
	SceneGameIntro(SceneGameIntro&) = delete;
	SceneGameIntro& operator=(const SceneGameIntro&) = delete;

public:
	SceneGameIntro();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;

	void ResultDataLoad();

private:
	SceneIds nextScene = SceneIds::SceneSelect;
	sf::Sprite background;
	std::vector<sf::Text> menuItems;
	std::vector<sf::FloatRect> menuBounds;
};