#pragma once
#include "Scene.h"
#include "SceneTemplate.h"

class SceneUpgrade : public Scene
{
protected:
	SceneUpgrade(SceneUpgrade&) = delete;
	SceneUpgrade& operator=(const SceneUpgrade&) = delete;

public:
	SceneUpgrade(SceneIds ids);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;

public:
	void SetCurrentScene(SceneIds id);


private:
	SceneIds nextScene;
};