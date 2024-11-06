#pragma once
#include "SceneTemplate.h"

class SceneWave2 : public SceneTemplate
{
protected:
	SceneWave2(SceneWave2&) = delete;
	SceneWave2& operator=(const SceneWave2&) = delete;

public:
	SceneWave2();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};