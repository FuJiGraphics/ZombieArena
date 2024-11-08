#pragma once
#include "SceneTemplate.h"

class SceneWave5 : public SceneTemplate
{
protected:
	SceneWave5(SceneWave5&) = delete;
	SceneWave5& operator=(const SceneWave5&) = delete;

public:
	SceneWave5();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
};