#pragma once
#include "SceneTemplate.h"

class SceneWave3 : public SceneTemplate
{
protected:
	SceneWave3(SceneWave3&) = delete;
	SceneWave3& operator=(const SceneWave3&) = delete;

public:
	SceneWave3();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};