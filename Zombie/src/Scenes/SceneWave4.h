#pragma once
#include "SceneTemplate.h"

class SceneWave4 : public SceneTemplate
{
protected:
	SceneWave4(SceneWave4&) = delete;
	SceneWave4& operator=(const SceneWave4&) = delete;

public:
	SceneWave4();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};